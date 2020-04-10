extern "C" {
#include <libtaomee/timer.h>
}


#include "login_auth_manager.h"
//===============================================================
//login_auth_manager_t Public
//===============================================================
void login_auth_manager_t::init(session_auth_cb_func cb_func, int timeout) 
{
	cb_func_ = cb_func;
	timeout_ = timeout_;

	init_list_sem();
	init_vect_sem();
}

int login_auth_manager_t::session_auth_req(const login_auth_input_t *p_input, 
		const fdsession_t *fdsess, int reg_time)
{
	int ret = 0;
	authdata_t *authdata = new authdata_t();
	if (!authdata) {
		ERROR_LOG("New Auth Data Error! Not Enough Resource!");
		return -1;
	}
	// authdata 初始化
	SNPRINTF_ATOA(authdata->primary_key, p_input->sess_id);
	authdata->guid	= p_input->guid;
	authdata->cli_cmd = p_input->cli_cmd;
	authdata->fdsess = fdsess;
	authdata->po_source_info = p_input->po_source_info;
	authdata->user_id = p_input->user_id;
	authdata->reg_time = reg_time;
	authdata->platform_id = p_input->platform_id;
	authdata->server_id = p_input->server_id;
	SNPRINTF_ATOA(authdata->sess_id, p_input->sess_id);
	SNPRINTF_ATOA(authdata->extra_data, p_input->extra_data);
	authdata->status_code = -1;

	lock_list_sem();
	string primary_key(authdata->primary_key);
	std::pair<primary_key_set_iter_t, bool> r1
		= primary_key_set_.insert(primary_key);
	if (!r1.second) {
		ERROR_LOG("Mutl Auth primary_key:%s fd:%d", 
				authdata->primary_key, fdsess->fd);
		ret = 1;
	} else {
		authdata->start_auth_time = get_now_tv()->tv_sec;
		authdata_list_.push_back(authdata);
		ret = 0;
	}
	unlock_list_sem();
	if (!ret) {
		return proc_session_auth_req(p_input);
	}
	return ret;
}

void login_auth_manager_t::proc_session_auth_req_with_db_rsp(string key, uint64_t real_userid)
{
	login_auth_map_iter_t it = login_auth_map_.find(key);
	if (it != login_auth_map_.end()) {
		login_auth_input_t *p_input = it->second;
		//p_input->user_id = real_userid;
		// 校验http请求
		c_http_client_thread *pht = new c_http_client_thread();
		if (!pht) {
			ERROR_LOG("New Http Client Thread Error! Not Enough Resource!");
			return;
		} 
		pht->init(p_input, &login_auth_http_callback, timeout_);
		// 释放内存
		delete it->second;
		login_auth_map_.erase(key);
	} else {
		ERROR_LOG("proc_session_auth_req_with_db_rsp not find key:%s real_userid:%lu", 
				key.c_str(), real_userid);
	}
}

#define SP_CHANNEL_ID (5000)
void login_auth_manager_t::session_auth_rsp(const login_auth_output_t *p_output)
{
	//delete p_output->po_source_info;
	lock_list_sem();
	authdata_list_iter_t it = authdata_list_.begin();
	for(; it != authdata_list_.end(); ++it) {
		authdata_t *authdata = *it;
		if (authdata->guid == p_output->guid) {
			// 验证数据记录到authdata中
			if (authdata->platform_id == SP_CHANNEL_ID) {
				authdata->platform_id = atoi(p_output->nick_name);
			}
			//authdata->user_id = p_output->user_id;
			authdata->status_code = p_output->status_code;
			//SNPRINTF_ATOA(authdata->nick_name, p_output->nick_name);
			SNPRINTF_ATOA(authdata->access_token, p_output->access_token);
			SNPRINTF_ATOA(authdata->extra_data, p_output->extra_data);
			// session有返回的数据放入vector容器中
			lock_vect_sem();
			authdata_vect_.push_back(authdata);
			unlock_vect_sem();
			// 清除该验证请求
			string primary_key(authdata->primary_key);
			primary_key_set_.erase(primary_key);
			authdata_list_.erase(it);
			// NOTI 无需释放authdata资源(authdata_vect_中会释放(proc_timer))
			break;
		}
	}
	unlock_list_sem();
}

void login_auth_manager_t::proc_timer()
{
	// session有返回的数据处理
	lock_vect_sem();
	authdata_vect_iter_t vect_iter = authdata_vect_.begin();
	while(vect_iter != authdata_vect_.end()) {
		authdata_t *authdata = *vect_iter;
		// 调用主程序callback函数
		cb_func_(authdata);
		vect_iter = authdata_vect_.erase(vect_iter);
		// 释放authdata资源
		delete authdata;
		// NOTI primary_key_set_、authdata_list_在此不需要处理(session_auth_rsp已经处理过了)
	}
	unlock_vect_sem();

	// 超时处理
	// NOTI 登陆验证timer粒度设置为秒级别, 因为需要用sem
	static int last_proc_time = get_now_tv()->tv_sec;
	int now = get_now_tv()->tv_sec;
	if (last_proc_time >= now) {
		return ;
	}
	// 超时处理
	last_proc_time = now;
	lock_list_sem();
	authdata_list_iter_t it = authdata_list_.begin();
	while(it != authdata_list_.end()) {
		authdata_t *authdata = *it;
		if (authdata->start_auth_time + AUTH_SESSION_TIME_OUT <= now) {
			// 超时
			authdata->status_code = ACCOUNT_E_CURL_TIMEOUT;	
			// 调用主程序callback函数
			cb_func_(authdata);
			// 清除该验证请求 
			string primary_key(authdata->primary_key);
			primary_key_set_.erase(primary_key);
			it = authdata_list_.erase(it);
			// 释放authdata资源
			delete authdata;
		} else {
			// 设置最近一次对list操作的时间
			last_proc_time = authdata->start_auth_time + AUTH_SESSION_TIME_OUT;
			break;
		}
	}
	unlock_list_sem();
}

void login_auth_manager_t::clear()
{
	lock_list_sem();
	authdata_list_iter_t it = authdata_list_.begin();
	while(it != authdata_list_.end()) {
		authdata_t *authdata = *it;
		string primary_key(authdata->primary_key);
		primary_key_set_.erase(primary_key);
		it = authdata_list_.erase(it);

		delete authdata;
	}
	authdata_list_.clear();
	primary_key_set_.clear();
	unlock_list_sem();

	lock_vect_sem();
	authdata_vect_iter_t vect_iter = authdata_vect_.begin();
	while(vect_iter != authdata_vect_.end()) {
		authdata_t *authdata = *vect_iter;
		vect_iter = authdata_vect_.erase(vect_iter);
		// 释放authdata资源
		delete authdata;
	}
	authdata_vect_.clear();
	unlock_vect_sem();

	login_auth_map_iter_t map_iter = login_auth_map_.begin();
	for(; map_iter != login_auth_map_.end(); ++map_iter) {
		delete map_iter->second;
	}
	login_auth_map_.clear();

	destroy_list_sem();
	destroy_vect_sem();
}

int login_auth_manager_t::proc_session_auth_req(const login_auth_input_t *p_input)
{
	switch(p_input->platform_id) {
#if 0
		case M1_CHANNEL_ID:		// 小米渠道
			{	
				login_auth_input_t *cache_input = 0;
				cache_input = (login_auth_input_t *)malloc(sizeof(*p_input));
				if (!cache_input) {
					ERROR_LOG("New Malloc login_auth_input_t Mem Fail! Not Enough Resource!");
					return 0;
				}
				memcpy(cache_input, p_input, sizeof(*p_input));
				// db请求
				db_query_real_userid_in db_in;
				db_in.set_zone_id(0);
				db_in.set_userid(cache_input->user_id);
				db_in.set_key(cache_input->primary_key);
				sMsgDispatcher.send_db_msg(0, db_in, true);
				// 缓存，等待db返回
				login_auth_map_[string(cache_input->primary_key)] = cache_input;
				break;
			}
#endif
		default:
			{
				c_http_client_thread *pht = new c_http_client_thread();
				if (!pht) {
					ERROR_LOG("New Http Client Thread Error! Not Enough Resource!");
					return -1;
				} 
				pht->init(p_input, &login_auth_http_callback, timeout_);
				break;
			}
	}
	return 0;
}

//===============================================================
//Global Func
//===============================================================
void login_auth_http_callback(login_auth_output_t *p_output)
{
	sLoginAuthMgr.session_auth_rsp(p_output);
}
