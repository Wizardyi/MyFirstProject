#ifndef __UTILS_H1_
#define __UTILS_H1_

#include "share/module/common.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <google/protobuf/util/json_util.h>
#include "proto/cache/cache.pb.h"

namespace utils
{
	
	 template <typename T>
     T string_to_number(std::string& s) {
         boost::ierase_last(s, "/r/n");
         T n = T();
         try {
             n = boost::lexical_cast<T>(s);
         } catch (boost::bad_lexical_cast& e) {
             ERROR_LOG("bad lexical cast: %s a, string:%s a", e.what(), s.c_str());
         }
         return n;
     }

 	 template <typename T>
     std::string number_to_string(T n) {
         std::string s;
         try {
             s = boost::lexical_cast<std::string>(n);
         } catch (boost::bad_lexical_cast& e) {
             ERROR_LOG("bad lexical cast: %s, number:%d", e.what(), static_cast<int>(n));
         }
         return s;
     }

	bool set(const std::string& strKey, const google::protobuf::Message& msg);
	bool get(const std::string& strKey, google::protobuf::Message& msg);
	  
	bool hset(const std::string& strKey, const std::string& strField, const google::protobuf::Message& msg);
	bool hget(const std::string& strKey, const std::string& strField, google::protobuf::Message& msg);

	//测试用函数
//	void CheckSetAndGet(cacheproto::CreateRole &req,cacheproto::CreateRole &ack);
}





























#endif
