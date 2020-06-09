#include "source_word.h"
#include "share/md5.h"
#include <curl/curl.h>
#include <openssl/hmac.h> 
#include "base64.h"
#include <exception>
#include "proto/share/share.pb.h"
#include <google/protobuf/util/json_util.h>

CSourceWord::CSourceWord(int platformId) {
	m_platformId = platformId;
	const CSourceConfigAuto* poConfig = CSourceAutoManager::Instance().GetSourceConfig(platformId);
	Init(poConfig);
}

void CSourceWord::Init(const CSourceConfigAuto* config) {
	if(config == nullptr) {
		ERROR_LOG("google source config null");
		return;	
	}
	config->GetAttr("accessKey", accessKey);
	config->GetAttr("url", m_strUrl);
	config->GetAttr("appid", appid);
	config->GetAttr("type", type);
}

void CSourceWord::PackQueryStr(const login_auth_input_t* input, char* postUrl, char* postData) {
	if (input == nullptr) {
		return;	
	}

	strcpy(postUrl, m_strUrl.c_str());

	shareproto::TextCheckJson datas;
	datas.set_accesskey(accessKey);
	datas.set_type(type);
	datas.set_appid(appid);

	shareproto::TextCheck* data = datas.mutable_data();
	data->Clear();
	google::protobuf::util::JsonStringToMessage(input->sess_id, data);

	std::string pstr;
	google::protobuf::util::MessageToJsonString(datas, &pstr);
	std::stringstream oss;
	oss << pstr;
	strcpy(postData, oss.str().c_str());
	std::cout << std::endl << postData << std::endl;
	DEBUG_LOG("Word Test URL:%s?%s", m_strUrl.c_str(), oss.str().c_str());
}

void CSourceWord::PackResponse(login_auth_output_t* output, const Json::Value& value) {
	if (output == nullptr || output->po_source_info == nullptr) {
		return;	
	}

	TRACE_LOG("step %d responce json:%s", output->step, value.toStyledString().c_str());

	std::cout << std::endl << value.toStyledString() << std::endl; 

	int code = 0;
	JSON_CAST_INT_(value, "code", code);
	switch(code)
	{
		case 1100:
			break;
		case 1902:
		case 1903:
		case 9100:
			output->status_code = ACCOUNT_E_TEXT_ERROR;
			return;
		default:
			break;
	}

	std::string subString;
	JSON_GET_STR_(value, "riskLevel", subString);
	std::string errStr = "REJECT";
	if (subString == errStr) {
		output->status_code = ACCOUNT_E_TEXT_ERROR;
		std::string subString;
		JSON_GET_STR_(value, "detail", subString);
		Json::Reader reader;                             
		Json::Value value1;
		if (!reader.parse(subString.c_str(), value1)) {
			output->status_code = ACCOUNT_E_WRONG_JSON;
			ERROR_LOG("json parse fail,%s", subString.c_str());
			return;
		}
		std::string subString1;
		JSON_GET_STR_(value1, "filteredText", subString1);
		snprintf(output->access_token, sizeof(output->access_token), "%s", subString1.c_str());
		std::cout << "YZX1:" << output->access_token << std::endl; 
		
		return;
	}
	 

	output->status_code = 0;
}



