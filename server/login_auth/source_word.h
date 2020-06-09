#pragma once
#include "source_config.h"

class CSourceWord : public CSourceBaseAuto {
public:

	CSourceWord(int platformId);
	virtual ~CSourceWord() {
	}
	void Init(const CSourceConfigAuto* config);
	void PackQueryStr(const login_auth_input_t* input, char* postUrl, char* postData);
	void PackResponse(login_auth_output_t* output, const Json::Value& backJson);

    virtual bool IsHttps() {
        return mIsHttps;
    }

	virtual bool IsPost() {
		return true;
	}

    bool mIsHttps;
    std::string accessKey;
    std::string type;
	std::string m_strUrl;
	std::string appid;
};
