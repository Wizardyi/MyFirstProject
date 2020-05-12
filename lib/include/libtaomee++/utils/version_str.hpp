/**
 * ============================================================
 * @file   version_str.hpp
 * @author jim (jim@taomee.com)
 * @date   2014-04-16 10:45:27
 *
 * 
 * @brief  
 * 
 * ============================================================
 */


#ifndef _VERSION_STR_H_
#define _VERSION_STR_H_


#include <libtaomee++/utils/md5.h>
#include <libtaomee++/utils/tcpip.h>
#include <string.h>
//得到 GCC __DATE__ 的 YYYYMMDD格式
inline const char * GetCompiledDate( const char * _date  )
{
    static char _buf[9] = {0};
    if(_buf[0] == 0)
    {
        static const char * _month[] =
        {
            "Jan",  "Feb",  "Mar",  "Apr",  "May",  "Jun",
            "Jul",  "Aug",  "Sep",  "Oct",  "Nov",  "Dec",
        };
        memcpy(_buf, _date + 7, 4);
        memcpy(_buf+6, _date + 4, 2);
        int month = 0;
        for(int i = 0; i < 12; i++)
        {
            if(memcmp(_month[i], _date, 3) == 0)
            {
                month = i+1;
                break;
            }
        }
        _buf[4] = month / 10 % 10 + '0';
        _buf[5] = month % 10 + '0';
    }
    return _buf;
}


inline std::string file_list_md5( std::vector<std::string> file_name_list)
{
	utils::MD5 md5;
    unsigned char md[16];
    int length,i;
    char buffer[1024];
	md5.reset();
    for (uint32_t i=0;i<file_name_list.size();i++ ) {
        std::ifstream fin(file_name_list[i].c_str(),std::ios::in|std::ios::binary);
        if (fin.is_open()){
            while(!fin.eof()){
                fin.read(buffer, 1024);
                length = fin.gcount();
                if (length > 0) { 
                    md5.update(buffer, length);
                } 
            } 
        }else{
            return "00000000000000000000000000000000";
        }
    } 
	return md5.toString();

}

// version_str::版本信息
//file_name_list:存放每台机器上都一样的文件:bin,so, txt,xml...
//最后会返回程序的版本信息
inline std::string get_version_str ( std::string version_str ,std::vector<std::string> file_name_list,bool is_out_ip =true ,uint32_t ip_type_flag =0x01 )
{
	if  (is_out_ip){
		return std::string("ip:")+get_ip_ex(ip_type_flag )+ std::string("|VERSION:")+version_str+"|compiled:"+GetCompiledDate(__DATE__) 
	   +"-"+__TIME__+"|md5:"+file_list_md5(file_name_list)	;
	}else{
		return std::string("VERSION:")+version_str+"|compiled:"+GetCompiledDate(__DATE__) 
	   +"-"+__TIME__+"|md5:"+file_list_md5(file_name_list)	;
	}
}
// version_str::版本信息
//file_name_list:存放每台机器上都一样的文件:bin,so, txt,xml...
//最后会返回程序的版本信息,长度定义在头部
inline const char * get_version_send_buf ( std::string version_str ,std::vector<std::string> file_name_list,bool is_out_ip =true ,uint32_t ip_type_flag =0x01 )
{
	static char version[256];
	memset(version,0,sizeof(version ));
	*((uint32_t*)version)=256;
	strncpy(version+18,
			get_version_str(version_str,file_name_list ,is_out_ip,ip_type_flag ).c_str(),
			256-18);
	return version;
}

#endif /* _VERSION_STR_H_ */
