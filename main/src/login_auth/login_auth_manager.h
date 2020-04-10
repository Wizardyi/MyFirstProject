/*
 * =========================================================================
 *
 *        Filename: login_auth_manager.h
 *
 *        Version:  1.0
 *        Created:  2013-08-30 11:38:48
 *        Description:  登陆验证管理
 *
 *        Author:  lyle (lyle@taomee.com)
 *        Company:  TAOMEE
 *
 * =========================================================================
 */
#ifndef  __LOGIN_AUTH_MANAGER_H__
#define  __LOGIN_AUTH_MANAGER_H__

#include <libtaomee++/proto/proto_util.h>
#include "http_client_thread.h"
#include "singleton.h"
#include "source_config.h"

#include <list>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <semaphore.h>

#define AUTH_SESSION_TIME_OUT	60
#define M1_CHANNEL_ID			4		// 小米渠道号

// 字符串赋值(字符串->字符串)
#define SNPRINTF_ATOA(dst, src) 	snprintf(dst, sizeof(dst), "%s", src);
// 字符串赋值(数字->字符串)
#define SPRINTF_ITOA(dst, src) 	sprintf(dst, "%lu", static_cast<uint64_t>(src));

using namespace std;

// 验证数据
struct authdata_t
{
public:
	authdata_t() {
		memset(this, 0, sizeof(authdata_t));
	}
public:
	/* 唯一id */
	uint64_t			guid;
	/* 本次请求的客户端命令 */
	uint32_t 			cli_cmd;
	/* 本次请求唯一键 */
	char 				primary_key[HCT_LOGINSESSION_KEY_MAX_LEN];
	/* 请求验证的fdsession */
	const fdsession_t	*fdsess;
	/* 用户ID，未知则填0 */
	uint32_t 			user_id;
	/* 用户注册时间, 未知则填0 */
	int					reg_time;
	/* 第三方平台id, 内部统一分配, platform_id */
	int					platform_id;
	/* 服务号，未知则填0 */
	int					server_id;
	/* 验证的授权token 、session id等 */
	char 				sess_id[HCT_TOKEN_MAX_LEN];
	/* 错误码，0表示成功 */
	int 				status_code;
	/* 用户昵称 */
	char 				nick_name[HCT_STR_MAX_SIZE];
	/* 第三方返回的token, 需要返回给客户端 */
	char				access_token[HCT_STR_MAX_SIZE];
	/* 客户端相关信息 */
	char 				extra_data[HCT_EXTRA_DATA_MAX_SIZE];
	/* 开始验证时刻(做验证过时处理) */
	int 				start_auth_time;
	/* 客户端版本号 */
	char				cli_version[HCT_STR_MAX_SIZE]; 
	/* 客户端ip地址 */
	char 				cli_ip[HCT_STR_MAX_SIZE];
	/* 客户端系统类型 */
	char				cli_platform[HCT_STR_MAX_SIZE];
	/* 客户端设备imei */
	char 				cli_equdid[HCT_STR_MAX_SIZE];
	/* 客户端设备型号 */
	char                cli_eqtype[HCT_STR_MAX_SIZE];
	/* 客户端mac地址 */
	char				cli_mac[HCT_STR_MAX_SIZE];
	/* 平台信息*/
	CSourceBaseAuto*			po_source_info;
};

class clidata_t 
{
public:
	clidata_t() {
		memset(this, 0, sizeof(clidata_t));
	}
public:
	/* 客户端版本号 */
	char				cli_version[HCT_STR_MAX_SIZE]; 
	/* 客户端ip地址 */
	char 				cli_ip[HCT_STR_MAX_SIZE];
	/* 客户端系统类型 */
	char				cli_platform[HCT_STR_MAX_SIZE];
	/* 客户端设备imei */
	char 				cli_equdid[HCT_STR_MAX_SIZE];
	/* 客户端设备型号 */
	char                cli_eqtype[HCT_STR_MAX_SIZE];
	/* 客户端mac地址 */
	char				cli_mac[HCT_STR_MAX_SIZE];
};

typedef std::list<authdata_t*> authdata_list_t;
typedef authdata_list_t::iterator authdata_list_iter_t;

typedef std::vector<authdata_t*> authdata_vect_t;
typedef authdata_vect_t::iterator authdata_vect_iter_t;

// 登陆session验证有结果后的回调函数
typedef void (*session_auth_cb_func) (authdata_t *authdata);

class login_auth_manager_t : public Singleton<login_auth_manager_t> 
{
public:
	/* *
	 * @brief 登陆session验证初始化
	 * @param cb_func 验证结束后处理函数
	 * @param timeout: http请求超时时长(单位: 秒), 0表示不超时
	 * */
	void init(session_auth_cb_func cb_func, int timeout = 0); 
	/* *
	 * @brief 输入验证信息请求
	 * @param p_input 验证的必须信息
	 * @param cli_data 客户端传来的一些统计信息
	 * @param reg_time 验证角色注册时间(未知则填0)
	 * @return 0:请求成功 1:重复请求 -1:系统错误
	 * */
	int session_auth_req(const login_auth_input_t *p_input, 
			const fdsession_t *fdsess,int reg_time = 0);
	/* *
	 * @breif db返回时登陆校验处理
	 * */
	void proc_session_auth_req_with_db_rsp(string key, uint64_t real_userid);
	/* *
	 * @brief 验证信息回包
	 * */
	void session_auth_rsp(const login_auth_output_t *p_output);
	/* *
	 * @brief timer处理(主要处理超时问题)
	 * */
	void proc_timer();
	/* *
	 * @brief clear
	 * */
	void clear();

private:
	/* *
	 * @brief session校验处理
	 * */
	int proc_session_auth_req(const login_auth_input_t *p_input);

private:
	void init_list_sem() { sem_init(&list_sem_, 0, 1); }
	void lock_list_sem() { sem_wait(&list_sem_); }
	void unlock_list_sem() { sem_post(&list_sem_); }
	void destroy_list_sem() { sem_destroy(&list_sem_); }
	
	void init_vect_sem() { sem_init(&vect_sem_, 0, 1); }
	void lock_vect_sem() { sem_wait(&vect_sem_); }
	void unlock_vect_sem() { sem_post(&vect_sem_); }
	void destroy_vect_sem() { sem_destroy(&vect_sem_); }

private:
	typedef std::set<string>			primary_key_set_t;
	typedef primary_key_set_t::iterator	primary_key_set_iter_t;

	typedef std::map<string, login_auth_input_t*> login_auth_map_t;
	typedef login_auth_map_t::iterator login_auth_map_iter_t;
private:
	session_auth_cb_func 		cb_func_;
	int 						timeout_;
	authdata_list_t				authdata_list_;			// session校验前数据存放容器
	primary_key_set_t			primary_key_set_;

	authdata_vect_t				authdata_vect_;			// session校验后数据存放容器
	
	login_auth_map_t			login_auth_map_;		// session校验等待db返回userid的数据缓存

	sem_t						list_sem_;
	sem_t						vect_sem_;
};

#define sLoginAuthMgr login_auth_manager_t::Instance()

//===============================================================
//Global Func
//===============================================================

void login_auth_http_callback(login_auth_output_t *p_output);

#endif  /*__LOGIN_AUTH_MANAGER_H__*/
