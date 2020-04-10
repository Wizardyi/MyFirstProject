#include "source_config.h"
#include "share/size_df.h"
#include "share/md5.h"
#include "source_word.h"

CSourceConfigAuto::CSourceConfigAuto()
	: m_strSourceName("")
	, m_dwSourceId(0)
	, m_oAttrMap()
{
}

CSourceConfigAuto::~CSourceConfigAuto()
{
}

bool CSourceConfigAuto::LoadFile(const char* pszFileName, tinyxml2::XMLElement* poSourceElem)
{
	if(pszFileName == NULL || poSourceElem == NULL)
	{
		return false;
	}

	const char* pszSourceName = poSourceElem->Attribute("name");
	const char* pszSourceId = poSourceElem->Attribute("id");
	if(pszSourceName == NULL || pszSourceId == NULL)
	{
		ERROR_LOG("Invalid table item in file: %s", pszFileName);
		return false;
	}

	m_strSourceName = pszSourceName;
	m_dwSourceId = atoi(pszSourceId);

	tinyxml2::XMLElement* poAttrElem = poSourceElem->FirstChildElement("attr");
	while(poAttrElem != NULL)
	{
		const char* pszAttrName = poAttrElem->Attribute("name");
		const char* pszAttrVal = poAttrElem->Attribute("val");
		if(pszAttrName == NULL || pszAttrVal == NULL)
		{
			ERROR_LOG("Invalid Attr item in source config: %s", pszSourceName);
			poAttrElem = poAttrElem->NextSiblingElement();
			continue;
		}

		m_oAttrMap.insert(std::make_pair(pszAttrName, pszAttrVal));
		poAttrElem = poAttrElem->NextSiblingElement();
	}

	return true;
}


bool CSourceConfigAuto::GetAttr(const std::string& strName, std::string& strAttr) const {
	auto it = m_oAttrMap.find(strName);
	if(it == m_oAttrMap.end()) {
		return false;	
	}
	
	strAttr = it->second;
	return true;
}

bool CSourceAutoManager::Init() {
	return true;
}

bool CSourceAutoManager::LoadFile(const char* pszFileName) {
	tinyxml2::XMLDocument doc;
	auto ret = doc.LoadFile(pszFileName);
	if (ret != tinyxml2::XML_SUCCESS)
	{
		ERROR_LOG("Load file failed %u", ret);
		return false;
	}

	tinyxml2::XMLElement* poSourceElem = doc.RootElement()->FirstChildElement("source");
	while (poSourceElem != NULL)
	{
		CSourceConfigAuto oSource;
		if (!oSource.LoadFile(pszFileName, poSourceElem))
		{
			ERROR_LOG("Load file %s failed", pszFileName);
			return false;
		}

		m_oSourceMap.insert(std::make_pair(oSource.GetId(), oSource));
		poSourceElem = poSourceElem->NextSiblingElement();
	}

	return true;
}

const CSourceConfigAuto* CSourceAutoManager::GetSourceConfig(uint32_t id) const
{
	CSourceMap::const_iterator it = m_oSourceMap.find(id);
	return it == m_oSourceMap.end() ? nullptr : &it->second;
}

CSourceBaseAuto* CSourceAutoManager::CreateSourceData(int platformId) {
	switch(platformId) {
		case 9527:
			return new CSourceWord(platformId);
		default:
			return nullptr;
	}
	ERROR_LOG("Invalid platfrom id:%d", platformId);
	return nullptr;
}




