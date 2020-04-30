#pragma once

#include <string>
#include <unordered_map>

class HostIpsConfigFile
{
    public:
        static HostIpsConfigFile& Instance() {
            if (sInstance == nullptr)
                sInstance = new HostIpsConfigFile();

            return *sInstance;
        }

        void load(const std::string& path);

        bool exist(const std::string& privateIp) const;
        std::string publicIp(const std::string& privateIp) const;

    private:
        std::unordered_map<std::string, std::string> mHostIps;

        static HostIpsConfigFile* sInstance;
};
