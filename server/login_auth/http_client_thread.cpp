/** 
 * ========================================================================
 * @file http_client_thread.cpp
 * @brief 
 * @author tonyliu
 * @version 1.0.0
 * @date 2013-08-26
 * Modify $Date: $
 * Modify $Author: $
 * Copyright: TaoMee, Inc. ShangHai CN. All rights reserved.
 * ========================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <json/json.h>
#include <libtaomee++/utils/md5.h>
#include <libtaomee++/proto/proto_util.h>
#include <openssl/hmac.h>

#include "http_client_thread.h"
#include "HMAC_SHA1.h"

#include "share/size_df.h"
#include "source_config.h"

using namespace std;


/**
 * @brief  构造函数
 * @param
 * @return
 */
c_http_client_thread::c_http_client_thread(): m_inited(false), m_post_timeout(0), m_callback_func(NULL), m_bIsHttps(false), m_bIsPost(false)
{
	memset(m_post_url, 0, sizeof(m_post_url));
	memset(m_post_data, 0, sizeof(m_post_data));
	m_back_data.len = 0;
	memset(m_back_data.data, 0, sizeof(m_back_data.data));
	memset(&m_output, 0, sizeof(m_output));
}

/**
 * @brief  析构函数
 * @param
 * @return
 */
c_http_client_thread::~c_http_client_thread()
{
	uninit();
}

/**
 * @brief   反初始化函数
 * @param   
 * @return
 */
int c_http_client_thread::uninit()
{
	if (!m_inited) {
		return -1;
	}

	m_inited = false;
	return 0;
}


/**
 * @brief   初始化函数
 * @param   url:  post地址, 长度不能超过HCT_URL_MAX_SIZE
 * @param   data: 发送的数据, 长度不能超过HCT_BUFF_MAX_SIZE
 * @return
 */
int c_http_client_thread::init(
		const login_auth_input_t *p_input,
		login_auth_callback_func callback_func,
		int timeout)
{
	if (m_inited || NULL == p_input || NULL == callback_func) {
		return -1;
	}
	if (0 != pack_http_data(p_input)) {
		return -1;
	}
	if(p_input->po_source_info != nullptr) {
		p_input->po_source_info->GetHeaderParam(m_strHttpHeaderParam);
		m_bIsHttps = p_input->po_source_info->IsHttps();
		m_bIsPost = p_input->po_source_info->IsPost();
	}
	m_callback_func = callback_func;
	m_post_timeout = timeout;

	/* Must initialize libcurl before any thread started */
	if (CURLE_OK != curl_global_init(CURL_GLOBAL_ALL)) {
		return -1;
	}

	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, start_transfer, this) != 0) {
		return -1;
	}
	/*reclaim resources itself*/
	pthread_detach(thread_id);

	m_inited = true;

	return 0;
}

int c_http_client_thread::pack_http_data(const login_auth_input_t *p_input)
{
	if(p_input->po_source_info == nullptr) {
		return -1;	
	}
	m_output.guid = p_input->guid;
	m_output.po_source_info = p_input->po_source_info;
	m_output.cli_cmd = p_input->cli_cmd;
	m_output.platform_id = p_input->platform_id;
	m_output.user_id = p_input->user_id;
	snprintf(m_output.extra_data, sizeof(m_output.extra_data), "%s", p_input->extra_data);

	p_input->po_source_info->PackQueryStr(p_input, m_post_url, m_post_data);

	//switch (p_input->platform_id)
	//{
	//	case PLATFORM_TAOMEE:
	//		pack_taomee_http_data(p_input);
	//		break;
	//	case PLATFORM_XYZS:
	//		pack_xyzs_http_data(p_input);
	//		break;
	//	default:
	//		return -1;
	//}

	return 0;
}

int c_http_client_thread::pack_taomee_http_data(const login_auth_input_t *p_input)
{
	//char buffer[HCT_BUFF_MAX_SIZE];
	///*sign值计算: 要求key值按ascii码从小到大排序好后*/
	////snprintf(buffer, sizeof(buffer), 
	////"channel=%d&extra_data=%s&game=%s&login_ip=%s&service=%d"
	////"&sess_id=%s&user_id=%lu&key=%s",
	////p_input->platform_id, p_input->extra_data, p_input->game_name, 
	////p_input->login_ip, p_input->proto_id,
	////p_input->sess_id, p_input->user_id, p_input->auth_sign);

	////snprintf(buffer, sizeof(buffer),
	////"app_id=%s&service=%u&session=%s&uid=%lu",
	////p_input->app_id, p_input->server_id, p_input->sess_id, p_input->user_id);

	////加密
	//unsigned char sign[HCT_STR_MAX_SIZE] = {0};

	//CHMAC_SHA1 mac;
	//mac.HMAC_SHA1((BYTE*)buffer, strlen(buffer), (BYTE*)p_input->app_secret, strlen(p_input->app_secret), sign);
	//bzero(buffer, sizeof(buffer));
	//snprintf(buffer, sizeof(buffer),
	//		"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
	//		sign[0], sign[1], sign[2], sign[3], sign[4], sign[5], sign[6], sign[7], sign[8], sign[9],
	//		sign[10], sign[11], sign[12], sign[13], sign[14], sign[15], sign[16], sign[17], sign[18], sign[19]);
	//buffer[40] = '\0';

	////TRACE_LOG("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
	////sign[0], sign[1], sign[2], sign[3], sign[4],
	////sign[5], sign[6], sign[7], sign[8], sign[9]);
	////TRACE_LOG("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
	////sign[10], sign[11], sign[12], sign[13], sign[14],
	////sign[15], sign[16], sign[17], sign[18], sign[19]);


	////snprintf(m_post_data, sizeof(m_post_data), 
	////		"app_id=%s&service=%u&session=%s&signature=%s&uid=%lu",
	////		p_input->app_id, p_input->server_id, p_input->sess_id, buffer, p_input->user_id);
	//TRACE_LOG("URL:%s?%s", m_post_url, m_post_data);

	return 0;
}

int c_http_client_thread::pack_xyzs_http_data(const login_auth_input_t *p_input)
{
	//snprintf(m_post_data, sizeof(m_post_data), 
	//		"appid=%s&token=%s&uid=%lu",
	//		p_input->app_id, p_input->sess_id, p_input->user_id);
	TRACE_LOG("URL:%s?%s", m_post_url, m_post_data);

	return 0;
}

void c_http_client_thread::do_post() {
	do{
		if (0 != http_post()) {
			break;
		}
		int32_t type = m_output.po_source_info->GetReturnType();
		if(type == ReturnType_Xml) {
			if(0 != xml_decode()) {
				break;
			}	
		}
		else if(type == ReturnType_Json){
			if (0 != json_decode()) {
				break;
			}
		}
		else if(type == ReturnType_NormalStr) {
			if (0 != str_decode()) {
				break;
			}
		}
	} while(false);
}

void c_http_client_thread::do_word_post() {
	do_post();
}


void * c_http_client_thread::start_transfer(void *p_data)
{
	TRACE_LOG("YZX:");
	assert(NULL != p_data);
	c_http_client_thread *p_thread = (c_http_client_thread *)p_data;
	uint32_t platformId = p_thread->m_output.po_source_info->GetPlatformId();
	TRACE_LOG("YZX:%d",platformId);
	switch(platformId) {
		case 9527:
			p_thread->do_word_post();
			break;
		default:
			p_thread->do_post();
			break;
	}
	//do {
	//	if (0 != p_thread->http_post()) {
	//		break;
	//	}

	//	if (0 != p_thread->json_decode()) {
	//		break;
	//	}
	//} while (false);
	/* assert to run m_callback_func */
	p_thread->m_callback_func(&p_thread->m_output);

	delete p_thread;
	p_thread = NULL;

	pthread_exit(0);
}

int c_http_client_thread::str_decode() {
	m_output.po_source_info->PackResponse(&m_output, m_back_data.data);
	return 0;
}

int c_http_client_thread::xml_decode() {
	const char* xml_start = m_back_data.data;
	tinyxml2::XMLDocument doc;
	auto ret = doc.Parse(xml_start);
	if(ret != tinyxml2::XML_SUCCESS) {
		ERROR_LOG("ret val parse failed %s, %u", xml_start, ret);
		return -1;
	}
	m_output.po_source_info->PackResponse(&m_output, doc.RootElement());

	return 0;
}

int c_http_client_thread::json_decode()
{
	const char *json_start = m_back_data.data;
	//const char *json_end = m_back_data.len > 0 ? (m_back_data.data + m_back_data.len - 1) : m_back_data.data;
	Json::Reader reader;
	Json::Value value;
	if (!reader.parse(json_start, value)) {
		m_output.status_code = ACCOUNT_E_WRONG_JSON;
		ERROR_LOG("json parse fail,%s", json_start);
		return -1;
	}
	m_output.po_source_info->PackResponse(&m_output, value);

	/*
	 * status_code   返回状态码  String  返回状态码  不可空  0表示验证成功
	 * user_id   uid Interger        当status_code为0时有此字段  234234
	 * nick_name 用户名  String  用户民  成功时有此字段  sdfsdf
	 * extra_data    客户端相关信息  String  客户端相关信息，原样返回    可空    nick:小摩尔
	 */

	//std::string key = "";
	//switch (m_output.platform_id)
	//{
	//	case PLATFORM_TAOMEE:
	//		key = "status_code";
	//		break;
	//	case PLATFORM_XYZS:
	//		key = "ret";
	//		break;
	//	default:
	//		return -1;
	//}

	//int status_code = value[key.c_str()].asInt();
	//JSON_CAST_INT(key.c_str(), status_code);
	//m_output.status_code = status_code;

	/*	string extra_data;
		JSON_GET_STR("extra_data", extra_data);
		snprintf(m_output.extra_data, sizeof(m_output.extra_data), "%s", extra_data.c_str());

		if (0 == status_code) {
		uint64_t user_id;
		JSON_CAST_INT("user_id", user_id);
		string nick_name;
		JSON_GET_STR("nick_name", nick_name);
		string access_token;
		JSON_GET_STR("token", access_token);

		m_output.user_id = user_id;
		snprintf(m_output.nick_name, sizeof(m_output.nick_name), "%s", nick_name.c_str());
		snprintf(m_output.access_token, sizeof(m_output.access_token), "%s", access_token.c_str());
		}
		*/
	return 0;
}

/**
 * @brief   发送post请求
 * @return  0-succ, -1-fail
 */
int c_http_client_thread::http_post()
{
	CURLcode res;
	read_data_t pool;

	pool.readptr = m_post_data;
	pool.len= strlen(m_post_data);
	pool.pos= 0;

	this->m_back_data.len = 0;

	CURL *curl = curl_easy_init();
	if(NULL == curl){
		m_output.status_code = CURLE_FAILED_INIT;
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, m_post_url);
	if(m_bIsPost) {
		TRACE_LOG("Http Post");
		/* Now specify we want to POST data */
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		/* we want to use our own read function */
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, callback_fill_post_data);
		/* pointer to pass to our read function */
		curl_easy_setopt(curl, CURLOPT_READDATA, &pool);
#ifdef USE_CHUNKED
		{
			struct curl_slist *chunk = NULL;

			chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
			res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			/* use curl_slist_free_all() after the *perform() call to free this
			   list again */
		}
#else
		/* Set the expected POST size. If you want to POST large amounts of data,
		   consider CURLOPT_POSTFIELDSIZE_LARGE */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t)pool.len);
#endif
	}
	if (m_post_timeout >= 0) {
		/* maximum time in seconds that you allow the libcurl transfer, zero means it never times out */
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, m_post_timeout);

		/*avoid to affect main thread*/
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	}

	/* we want to use our own write function */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_post_back);
	/* Set a pointer to our struct to pass to the callback */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->m_back_data));

	/* get verbose debug output please */
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	if(m_strHttpHeaderParam.size() > 0) {
		struct curl_slist *plist = NULL;
		for(auto param : m_strHttpHeaderParam) {
			TRACE_LOG("header param:%s", param.c_str());
			plist = curl_slist_append(plist, param.c_str());  
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);  		 
	}
	//if(m_bIsHttps) {
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);  
	//}
#ifdef DISABLE_EXPECT
	/*
	   Using POST with HTTP 1.1 implies the use of a "Expect: 100-continue"
	   header.  You can disable this header with CURLOPT_HTTPHEADER as usual.
NOTE: if you want chunked transfer too, you need to combine these two
since you can only set one list of headers with CURLOPT_HTTPHEADER. */

	/* A less good option would be to enforce HTTP 1.0, but that might also
	   have other implications. */
	{
		struct curl_slist *chunk = NULL;

		chunk = curl_slist_append(chunk, "Expect:");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		/* use curl_slist_free_all() after the *perform() call to free this
		   list again */
	}
#endif
	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl);

	/* always cleanup */
	curl_easy_cleanup(curl);

	if(CURLE_OK != res) {
		/* we failed */
		TRACE_LOG("http failed :%d", res);
		m_output.status_code = res;
		return -1;
	}

	return 0;
}

/**
 * @brief   获取post返回数据
 * @return post返回数据
 *
 */
std::string c_http_client_thread::get_post_back_data()
{
	return std::string(this->m_back_data.data, this->m_back_data.len);
}


//=========================回调函数部分=========================
size_t c_http_client_thread::callback_fill_post_data(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	if(size * nmemb < 1){
		return 0;
	}

	read_data_t *pool = (read_data_t *)userdata;
	size_t len = pool->len - pool->pos;
	if (len > size * nmemb) {
		len = size * nmemb;
	}

	memcpy(ptr, pool->readptr + pool->pos, len);
	pool->pos += len;

	return len;
}

size_t c_http_client_thread::callback_get_post_back(void *buffer, size_t size, size_t nmemb, void *stream)
{
	post_back_t *back_data = (post_back_t*)stream;

	/*no space to store return data*/
	if (back_data->len >= sizeof(back_data->data) - 1) {
		return 0;
	}

	/*store as much as possible*/
	size_t cp_len = nmemb * size;
	if (back_data->len + nmemb * size >= sizeof(back_data->data)) {
		cp_len = sizeof(back_data->data) - back_data->len - 1;
		//return CURLE_WRITE_ERROR;
	}

	memcpy(back_data->data + back_data->len, (char*)buffer, cp_len);
	back_data->len += cp_len;
	back_data->data[back_data->len] = '\0';

	return nmemb;
}

