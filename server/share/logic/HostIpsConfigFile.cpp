extern "C" {
#include <libtaomee/log.h>
}
#include "HostIpsConfigFile.h"
#include "CSVFile.h"

HostIpsConfigFile* HostIpsConfigFile::sInstance = nullptr;

void HostIpsConfigFile::load(const std::string& path)
{
	mHostIps.clear();
    CSVFile csv(path);

    for (uint32_t i = 0; i < csv.numRow(); i++) {
        std::string privateIp = csv.item(i, 0);
        std::string publicIp = csv.item(i, 1);

        if (privateIp != "" && publicIp != "") {
            mHostIps[privateIp] = publicIp;
        }
    }

	auto itor = mHostIps.begin();
	for (; itor != mHostIps.end(); itor++) {
		INFO_LOG("inside network ip:%s, outside network ip:%s",
				(itor->first).c_str(), (itor->second).c_str());
	}
}

bool HostIpsConfigFile::exist(const std::string& privateIp) const
{
    return mHostIps.count(privateIp) > 0;
}

std::string HostIpsConfigFile::publicIp(const std::string& privateIp) const
{
    auto it = mHostIps.find(privateIp);

    return it != mHostIps.end() ? it->second : privateIp;
}
