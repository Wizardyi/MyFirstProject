#pragma once

#include "tinyxml2.h"
#include <json/json.h>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include "singleton.h"
#include "http_client_thread.h"
extern "C" {
#include <libtaomee/log.h>
}

#define JSON_CAST_DOUBLE_(value, key, val) \
	do {\
		switch (value[key].type()) {\
			case Json::realValue:\
					    val = value[key].asDouble();\
			break;\
			case Json::stringValue:\
					       val = atol(value[key].asString().c_str());\
			break;\
			default:\
				output->status_code = ACCOUNT_E_WRONG_JSON;\
			return ;\
		}\
	} while(false)


#define JSON_CAST_INT_(value, key, val) \
	do {\
		switch (value[key].type()) {\
			case Json::intValue:\
					    val = value[key].asInt();\
			break;\
			case Json::stringValue:\
					       val = atol(value[key].asString().c_str());\
			break;\
			default:\
				output->status_code = ACCOUNT_E_WRONG_JSON;\
			return ;\
		}\
	} while(false)

#define JSON_GET_STR_(value, key, val) \
	do {\
		if ( !value[key].isString()) {\
			output->status_code = ACCOUNT_E_WRONG_JSON;\
			return ;\
		}\
		val = value[key].asString();\
	} while(false)

#define JSON_GET_OBJECT_(value, key, val) \
	do {\
		if ( value[key].type() != Json::objectValue) {\
			output->status_code = ACCOUNT_E_WRONG_JSON;\
			return ;\
		}\
		val = value[key];\
	} while(false)

#define JSON_GET_BOOL_(value, key, val) \
	do {\
		if ( !value[key].isBool()) {\
			output->status_code = ACCOUNT_E_WRONG_JSON;\
			return ;\
		}\
		val = value[key].asBool();\
	} while(false)

typedef std::vector<std::string> StringVector;


class CSourceConfigAuto
{
public:
	CSourceConfigAuto();
	~CSourceConfigAuto();

	bool LoadFile(const char* pszFileName, tinyxml2::XMLElement* poSourceElem);
	const std::string& GetName() const { return m_strSourceName; }

	bool GetAttr(const std::string& strName, std::string& strAttr) const;

	uint32_t GetId() { return m_dwSourceId; }
private:
	std::string		m_strSourceName;
	uint32_t		m_dwSourceId;
	std::unordered_map<std::string, std::string> m_oAttrMap;
};

class CSourceAutoManager : public Singleton<CSourceAutoManager>
{
public:
	bool Init();

	bool LoadFile(const char* pszFileName);

	const CSourceConfigAuto* GetSourceConfig(uint32_t id) const;

	CSourceBaseAuto* CreateSourceData(int platformId);
private:
	typedef std::unordered_map<uint32_t, CSourceConfigAuto> CSourceMap;

	CSourceMap		m_oSourceMap;
};

enum ReturnType{
	ReturnType_NormalStr = 0,
	ReturnType_Json = 1,
	ReturnType_Xml = 2
};

class CSourceBaseAuto {
public:
	CSourceBaseAuto():m_platformId(0) {}
	virtual ~CSourceBaseAuto() {}

	virtual void Init(const CSourceConfigAuto* config) = 0;

	virtual void PackQueryStr(const login_auth_input_t* input, char* postUrl, char* postData) = 0;

	virtual void PackQueryStr(const login_auth_output_t* output, char* postUrl, char* postData) {}

	virtual void PackResponse(login_auth_output_t* output, const Json::Value& backJson) {}
	virtual void PackResponse(login_auth_output_t* output, const tinyxml2::XMLElement* root) {}
	virtual void PackResponse(login_auth_output_t* output, const char* str) {}

	virtual void GetHeaderParam(std::vector<std::string>& roParam) {}

	virtual int32_t GetReturnType() {
		return ReturnType_Json;
	}

	virtual bool IsHttps() {
		return false;
	}

	virtual bool IsPost() {
		return true;
	}

	void SetSourceNum(const std::string& strSourceNum) {
		m_strSourceNum = strSourceNum;	
	}

	std::string GetSourceNum() { 
		return m_strSourceNum;
	}

	void SetSdkRetJson(const std::string& json) {
		m_strSdkRetJson = json;	
	}

	std::string GetSdkRetJson() { 
		return m_strSdkRetJson;
	}

	uint32_t GetPlatformId() {
		return m_platformId;	
	}
protected:
	uint32_t   m_platformId;
	std::string m_strSourceNum;
	std::string m_strSdkRetJson;
};


