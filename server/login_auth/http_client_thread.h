/** 
 * ========================================================================
 * @file http_client_thread.h
 * @brief 
 * @author tonyliu
 * @version 1.0.0
 * @date 2013-08-26
 * Modify $Date: $
 * Modify $Author: $
 * Copyright: TaoMee, Inc. ShangHai CN. All rights reserved.
 * ========================================================================
 */

#ifndef H_HTTP_CLIENT_THREAD_H_20130826
#define H_HTTP_CLIENT_THREAD_H_20130826
#include <iostream>
#include <curl/curl.h>
#include <stdint.h>

#define HCT_KEY_MAX_LEN 64
#define HCT_LOGINSESSION_KEY_MAX_LEN 1024
#define HCT_STR_MAX_SIZE 64
#define HCT_TOKEN_MAX_LEN 2048 
#define HCT_URL_MAX_SIZE 256
#define HCT_IP_MAX_SIZE 32
#define HCT_EXTRA_DATA_MAX_SIZE 1024
#define HCT_BUFF_MAX_SIZE_ 8192
#define HCT_APP_ID_MAX_SIZE 33

class CSourceBaseAuto;


//=====================================公用结定义部分=====================================
enum e_account_error_code {
	/*curl错误码*/
	ACCOUNT_E_CURL_INIT   = CURLE_FAILED_INIT,       /**<curl初始化失败*/
	ACCOUNT_E_CURL_WRITE   = CURLE_WRITE_ERROR,       /**<调用写回调函数失败*/
	ACCOUNT_E_CURL_READ    = CURLE_READ_ERROR,        /**<调用读回调函数失败*/
	ACCOUNT_E_CURL_TIMEOUT = CURLE_OPERATION_TIMEDOUT,/**<验证超时*/

	ACCOUNT_E_WRONG_JSON = 101,/**<json_decode failed*/

	/*account验证返回的错误码*/
	ACCOUNT_E_SUCCESS = 0,                      /**<处理成功*/
	ACCOUNT_E_SYSTEM_ERROR = 1001,              /**<系统处理错误*/
	ACCOUNT_E_INVALID_PARAMS = 1002,            /**<无效的参数*/
	ACCOUNT_E_INVALID_ACTION = 1003,            /**<无效的action值*/
	ACCOUNT_E_SYSTEM_BUSY = 1004,               /**<系统繁忙*/
	ACCOUNT_E_INVALID_SIGN = 1006,              /**<签名失败*/
	ACCOUNT_E_REQUEST_TIMEOUT = 1007,           /**<客户端请求时间戳已经过期*/
	ACCOUNT_E_TOO_MUCH_WRONG = 1010,            /**<接口错误次数过多或接口尝试次数过多，需要验证码才能调用接口*/
	ACCOUNT_E_PASSWD_ALREADY_SET = 1011,        /**<无线第一次设置密码时密码已经被设置过了*/
	ACCOUNT_E_WRONG_OLD_PASSWD = 1012,          /**<用老密码修改新密码时老密码错误*/
	ACCOUNT_E_UDID_NOT_REGISTER = 1013,         /**<查询设备号对应米米号时设备号未注册过*/
	ACCOUNT_E_CHECK_VERIFY_CODE_FAILED = 1014,  /**<验证码错误*/
	ACCOUNT_E_CHECK_USERID_ERROR = 1015,        /**<米米号没有绑定邮箱*/
	ACCOUNT_E_CHECK_USER_EMAIL_FAILE = 1016,    /**<输入的邮箱与米米号不对应*/
	ACCOUNT_E_CHECK_EMAIL = 1017,               /**<邮箱格式不正确*/
	ACCOUNT_E_EMAIL_EXISTED = 1019,             /**<邮箱已经存在，不能绑定*/
	ACCOUNT_E_EMAIL_BIND_ERROR = 1020,          /**<邮箱绑定失败（但是其他操作成功，如注册时绑定那么注册成功但是绑定失败）*/
	ACCOUNT_E_SYS_ERROR = 1018,                 /**<系统错误*/
	ACCOUNT_E_SEND_ERROR = 1021,                /**<邮件发送失败*/
	ACCOUNT_E_PWD_ERROR = 1103,                 /**<密码错误*/
	ACCOUNT_E_NOT_EXISTED_ERROR = 1105,         /**<米米号或者邮箱不存在*/
	ACCOUNT_E_ADD_OPENID_ERROR = 1106,          /**<登录成功，绑定失败*/
	ACCOUNT_E_LOGIN_ERROR = 1108,               /**<设备被冻结无法登陆*/
	ACCOUNT_E_BIND_ERROR = 1109,                /**<绑定第三方账号失败*/
	ACCOUNT_E_GETTHIRD_ERROR = 1110,            /**<获取第三方账号失败*/
	ACCOUNT_E_GETBIND_ERROR = 1111,             /**<已经绑定不能重复绑定*/
	ACCOUNT_E_VERIFY_ERROR = 1112,              /**<第三方登录验证失败，用户没有登录或者已经过期等*/
	ACCOUNT_E_UDID_ERROR = 1113,                /**<自定义注册用户名不能全为数字*/
	ACCOUNT_E_TEXT_ERROR = 1114					/**文本内容有敏感内容*/ 
};

typedef struct login_auth_input {
	login_auth_input()
	{
		bzero(this, sizeof(login_auth_input));
	}
	uint64_t  guid;
	/*调用者自己生成*/
	//char primary_key[HCT_KEY_MAX_LEN];      /**<本次请求唯一键*/
	uint32_t cli_cmd;						/*客户端的命令*/

	/*配置文件中获取*/
	int proto_id;                           /**<登陆验证协议编码*/
	//char auth_url[HCT_URL_MAX_SIZE];        /**<登陆验证URL*/
	//char auth_sign[HCT_STR_MAX_SIZE];       /**<登陆验证签名*/
	char game_name[HCT_KEY_MAX_LEN];        /**<游戏名称: ahero、ago、astorm*/
	char login_ip[HCT_IP_MAX_SIZE];         /**<用户登录IP*/

	/*客户端传过来*/
	char sess_id[HCT_TOKEN_MAX_LEN];        /**<验证的授权token、session id等*/
	//char app_id[HCT_APP_ID_MAX_SIZE];		/* app_id */
	//char app_secret[HCT_EXTRA_DATA_MAX_SIZE];/* app_secret */
	int platform_id;                        /**<第三方平台id, 内部统一分配*/
	uint32_t server_id;						/*服务号*/
	uint32_t user_id;						/*玩家id*/
	char extra_data[HCT_EXTRA_DATA_MAX_SIZE];/**<客户端相关信息*/
	CSourceBaseAuto*	po_source_info;		     /* 平台信息*/
} login_auth_input_t;

typedef struct login_auth_output {
	login_auth_output()
	{
		bzero(this, sizeof(login_auth_output));
		status_code = 1;
	}
	uint64_t guid;
	uint32_t step;
	//char primary_key[HCT_KEY_MAX_LEN];         /**<本次请求唯一键*/
	uint32_t cli_cmd;						/*客户端的命令*/
	int status_code;                            /**<错误码，0表示成功*/
	int platform_id;                        /**<第三方平台id, 内部统一分配*/
	char nick_name[HCT_STR_MAX_SIZE];           /**<用户昵称*/
	char access_token[HCT_STR_MAX_SIZE];        /**<第三方返回的token, 需要返回给客户端*/
	char extra_data[HCT_EXTRA_DATA_MAX_SIZE];   /**<客户端相关信息*/
	uint32_t user_id;						/*玩家id*/
	CSourceBaseAuto*	po_source_info;		     /* 平台信息*/
} login_auth_output_t;

typedef void (*login_auth_callback_func) (login_auth_output_t *p_output);
//========================================================================================


class c_http_client_thread
{

	public:

		c_http_client_thread();
		~c_http_client_thread();

		/**
		 * @brief   初始化函数
		 * @param   p_input:  输入参数
		 * @param   callback_func: http返回包处理函数
		 * @param   timeout: http请求超时时长(单位: 秒), 0表示不超时
		 * @return  0-succ, -1-fail
		 */
		int init(const login_auth_input_t *p_input, login_auth_callback_func callback_func, int timeout);

	protected:
		/**
		 * @brief   反初始化函数
		 * @param   无
		 * @return  0-succ, -1-fail
		 */
		int uninit();

		/**
		 * @brief   发送post请求
		 * @return  0-succ, -1-fail
		 */
		int http_post();

		/**
		 * @brief   json字符串解析
		 * @return  0-succ, -1-fail
		 */
		int json_decode();

		int xml_decode();

		int str_decode();

		/**
		 * @brief   获取post返回数据
		 * @return  post返回数据
		 */
		std::string get_post_back_data();

		void do_post();

        void do_word_post();
	private:
		/**
		 * @brief   组装http请求data部分
		 * @return  0-succ, -1-fail
		 */
		int pack_http_data(const login_auth_input_t *p_input);
		// 淘米
		int pack_taomee_http_data(const login_auth_input_t *p_input);
		// XY 苹果助手
		int pack_xyzs_http_data(const login_auth_input_t *p_input);

		static void * start_transfer(void *);

		static size_t callback_fill_post_data(void *ptr, size_t size, size_t nmemb, void *userdata);
		static size_t callback_get_post_back(void *buffer, size_t size, size_t nmemb, void *stream);

	protected:
		typedef struct {
			const char *readptr;
			size_t len;
			size_t pos;
		} read_data_t;

		typedef struct {
			char data[HCT_BUFF_MAX_SIZE_];
			size_t len;
		} post_back_t;

	private:
		bool m_inited;
		int m_post_timeout;
		char m_post_url[HCT_URL_MAX_SIZE];
		char m_post_data[HCT_BUFF_MAX_SIZE_];
		post_back_t m_back_data;

		login_auth_output_t m_output;
		login_auth_callback_func m_callback_func;

		std::vector<std::string> m_strHttpHeaderParam;
		bool m_bIsHttps;
		bool m_bIsPost;
};

#endif
