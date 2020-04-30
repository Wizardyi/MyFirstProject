#ifndef SHARE_FUN_H
#define SHARE_FUN_H
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <time.h>
#include <memory>
#include <google/protobuf/message.h>
extern "C" {
#include <libtaomee/tm_dirty/tm_dirty.h>
#include <libtaomee/log.h>
}
#include <libtaomee++/conf_parser/xmlparser.hpp>
#include <libtaomee++/random/random.hpp> 
#include "share/config/size_df.h"
#include <openssl/sha.h> 
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <sys/timeb.h>
// #include "config_data/DataEnums.h"
// #include "BattleHero.h"
#include <google/protobuf/util/json_util.h>
#include <zlib.h>

#define STRCPY_SAFE(buf, str) \
    do { \
        int buflen = sizeof(buf); \
        buf[buflen - 1] = '\0';\
        strncpy(buf, str, buflen - 1); \
    } while (0);

#define BIT_SET(x,n) ((x)|=(1<<(n)))
#define BIT_CLR(x,n) ((x)&=~(1<<(n)))
#define BIT_CHK(x,n) (((x)>>(n))&0x1)

struct item_conf_t
{
	uint32_t item_id = 0;
	uint32_t cnt	= 0;
};

// 玩家身上存放的物品信息 存储除了家具和服装外的其他类型物品
struct normal_item_t {
	uint32_t id = 0;
	uint32_t count = 0;
	uint32_t get_time = 0;
};

class ShareUtils 
{
	public:
		// 判断点 b 是否在点 a 的 r 范围内
		static bool IsInRange(float a_x, float a_y, float b_x, float b_y, float r)
		{
			if (std::pow(a_x - b_x, 2) + std::pow(a_y - b_y, 2) <= std::pow(r, 2)) {
				return true;
			}
			else {
				return false;
			}
		}

		// 单引号转义
		static std::string TransferStr(const std::string& str)
		{
			std::string ret;
			for (size_t i=0; i<str.length(); i++) {
				if (str[i] == '\'') {
					ret += '\\';
					ret += str[i];
				}
				else {
					ret += str[i];
				}
			}
			return ret;
		}
		
		// 获取一个月之内的毫秒数
		static uint32_t GetMilliSecs() 
		{
			struct timeb tb;
			ftime(&tb);
			return time(nullptr)%(30*24*60*60)*1000 + tb.millitm;
		}
		
		static void _str2Set(const std::string& str, std::set<uint32_t>& roSet)
		{
			std::vector<std::string> oVec = ShareUtils::split(str, ',');
			for(auto it : oVec) {
				uint32_t cityId = atoi(it.c_str());	
				roSet.insert(cityId);
			}
		}
		
		static std::string _set2Str(std::set<uint32_t>& roSet)
		{
			uint32_t size = roSet.size();
			std::stringstream oss;
			uint32_t cnt = 0;
			for(auto i : roSet) {
				oss << i;	
				if(++cnt < size) {
					oss << ",";		
				}
			}

			return oss.str();
		}
		
		static void StrToVector(const std::string& str, std::vector<uint32_t>& vec)
		{
			std::vector<std::string> strVec = ShareUtils::split(str, ',');
			for (auto strValue : strVec) {
				vec.push_back(atoi(strValue.c_str()));
			}
		}

		static void StrToVector(const std::string& str, std::vector<std::vector<uint32_t> >& vec)
		{
			std::vector<std::string> strVec = ShareUtils::split(str, ';');
			for (auto strValue : strVec) {
				std::vector<uint32_t> _vec;
				ShareUtils::StrToVector(strValue, _vec);
				vec.push_back(_vec);
			}
		}

		static void get_random_list(
			uint32_t start, uint32_t end, uint32_t count, std::vector<uint32_t>& vec_ret)
		{
			if (start >= end || (end - start + 1) < count) {
				return;
			}

			std::vector<uint32_t> temp;
			temp.clear();
			for (uint32_t i=0; i<(end-start+1); i++) {
				temp.push_back(start+i);
			}

			uint32_t rand_max = temp.size()-1;
			for (uint32_t i = 0; i < count; i++) {
				uint32_t rand = taomee::ranged_random(0, rand_max);
				vec_ret.push_back(temp[rand]);
				temp[rand] = temp[rand_max];
				rand_max--;
			}

			// auto itor = vec_ret.begin();
			// DEBUG_LOG("get random list. start:%u, end:%u, count:%u", start, end, count);
			// for (; itor != vec_ret.end(); itor++) {
			// 	DEBUG_LOG(" rand:%u", *itor);
			// }
		}
	
		// 字符串时间转时间戳 %Y-%m-%d %H:%M:%S
		static uint32_t TimeStrToUnint(std::string strTime)
		{
			struct tm tm_time = {};
			strptime(strTime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);
			return mktime(&tm_time);
		}
		static uint32_t GetFightValue(uint32_t herohp,uint32_t herostrength,uint32_t solderhp,uint32_t solderatt,uint32_t heroTactics,uint32_t skilllevel,uint32_t curldef,uint32_t physicaldef)
		{
			return (uint32_t)(sqrt((uint64_t)herohp*herostrength) + sqrt((uint64_t)solderhp*solderatt) + heroTactics*std::pow(skilllevel,0.3f) + curldef + physicaldef);
		}

  static int SplitLine(char **templa, int templatecount, char *pkt,char space)
  {      
          if (pkt == nullptr)
                  return 0;
  
          int i = 0;
          while (*pkt == space)
                  ++pkt;
          while (*pkt != 0)
          {
                 if ((*pkt == '\r') || (*pkt == '\n') || (*pkt == '\t'))
                 {
                         memmove(pkt,pkt+1,strlen(pkt+1)+1);
                 }
                 else if (i == 0)
                 {
                         templa[i] = pkt;
                         ++i;
                 }
                 else if ((*pkt == space) && (i < templatecount))
                 {
                         *pkt = 0;
                         ++pkt;
                         while (*pkt == space)
                                 ++pkt;
                         templa[i] = pkt;
                         ++i;
                 }
                 else
                 {
                         ++pkt;
                 }
                 if(i >= templatecount)
                         break;
         }       
         return i;
    }  

	static inline std::vector<std::string> split(const std::string &s, char delim)
	 {
		 std::vector<std::string> elems;
	 
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			elems.push_back(item);
		}
		return elems;
	 }

	static inline void split(const std::string& str, const std::string& delim, std::vector<std::string>& result)
	{
		size_t end = 0;
		size_t begin = 0;
		while (end != std::string::npos) {
			end = str.find_first_of(delim, begin);
			if (end != std::string::npos) {
				result.push_back(str.substr(begin, end - begin));
			}
			else {
				result.push_back(str.substr(begin, std::string::npos));
			}
				begin = end + 1;
		}
	}
	  // 获取当天是周几
	 static inline uint32_t get_week() 
	 {
		time_t rawtime;
		time(&rawtime);
		struct tm * timeinfo = localtime(&rawtime);
		return timeinfo->tm_wday;
	}   

	 // 获取当天是几号
	 static inline uint32_t get_day_of_month()
	 {
		time_t rawtime;
		time(&rawtime);
		struct tm * timeinfo = localtime(&rawtime);
		return timeinfo->tm_mday;
	 }

	 // 获取从给定时间到目前的周数
	 static inline int get_weeks_from_time(time_t time_)
	 {
		 // 先求给定时间的周一凌晨 5:00
		struct tm * timeinfo = localtime(&time_);            
		timeinfo->tm_hour = 23;                            
		timeinfo->tm_min = 59;                             
		timeinfo->tm_sec = 59;                             
		time_t rawtime = mktime(timeinfo);                             
		timeinfo->tm_wday = timeinfo->tm_wday == 0 ? 7 : timeinfo->tm_wday;
		uint32_t o_time = rawtime - timeinfo->tm_wday * 24 * 60 * 60 + DAY_START_TIME*60*60;
		return time(nullptr) <= o_time ? 1 : (time(nullptr) - o_time)/(7*24*60*60)+1;
	 }

	 // 获取当前的月份
	 static inline int get_month(time_t time) {
		 struct tm date;
		 localtime_r(&time, &date);
		 return date.tm_mon;
	 }

	 // 获取当前时间的天
	 static inline std::string get_day(time_t time) {
		std::stringstream str_day;
		struct tm date;
		localtime_r(&time, &date);
		str_day << (date.tm_year+1900) << "_" 
			<< (date.tm_mon+1) << "_"
			<< date.tm_mday;
		return str_day.str();
	 }

	// redis 上存储的分数，需要加上一个时间戳权重
	// 以保证相同分数的，越早提交排名越靠后
	// 策划说：不希望后面的玩家就算花钱也追不上前面的玩家
	static uint64_t deal_with_score(uint32_t score)
	{
		return ((uint64_t) time(NULL) << 32) | score;
	}

	// redis 上存储的经过处理得分数，重新转换成正常分数和获取时间戳
	static void restore_score(uint64_t b_score, uint32_t& a_score, uint32_t& time) 
	{
		a_score = (uint32_t)b_score;
		time = (uint32_t)(b_score >> 32);
	}
 
	static uint32_t restore_score(uint64_t score)
	{
		return (uint32_t)score;
	}

	// 该事件权重只能用于一天内，如果时间需要长，则把总时间增加 高32位：分数，低32位：时间权重
	static uint64_t deal_with_score_for_world_war(uint32_t score) 
	{
		uint32_t t = ShareUtils::get_day_end_time(time(nullptr)) - time(nullptr); // 获取时间权重，越早时间权重越大
		return ((uint64_t) score << 32) | t;
	}

	static void restore_score_for_world_war(uint64_t b_score, uint32_t& a_score, uint32_t& t)
	{
		a_score = (uint32_t)(b_score >> 32);
		t = (uint32_t)b_score;
	}

	static uint32_t restore_score_for_world_war(uint64_t score)
	{
		return (uint32_t)(score >> 32);
	}

	// 根据房间id和房间编号生成房间唯一id
	static uint64_t get_room_uniquueid(uint32_t userid, uint32_t roomid)
	{
		return ((uint64_t) roomid << 32) | userid;
	}

	// 获取当天结束时候的时间戳
	// 因为业务需要，游戏中每一天从当天自然时间凌晨5点开始
	// 到第二天自然时间凌晨5点结束 
	static time_t get_day_end_time(time_t time)
	{
		struct tm date;
		localtime_r(&time, &date);
		if (date.tm_hour < DAY_START_TIME) {
			date.tm_hour = DAY_START_TIME;
			date.tm_min = 0;
			date.tm_sec = 0;
			return mktime(&date);
		}
		else {
			date.tm_hour = DAY_START_TIME;
			date.tm_min = 0;
			date.tm_sec = 0;
			return mktime(&date) + DAY_SECS;
		}
	}
	// 获取当天开始时候的时间戳
	// 因为业务需要，游戏中每一天从当天自然时间凌晨5点开始
	// 到第二天自然时间凌晨5点结束 
	static time_t get_day_start_5h_time(time_t time)
	{
		return get_day_end_time(time) - DAY_SECS;
	}

	// 需求：国战投票时间，今晚21点之前投票，票数算在今天的投票中，21点之后投票，算在明天的投票中
	// 获取这个投票的时间戳
	static time_t get_world_war_vote_time(time_t time)
	{
		// 先获取当日凌晨5点时间戳
		time_t _5 = get_day_start_5h_time(time);
		time_t _21 = _5 + 16*60*60;
		if (time < _21) {
			return get_day_start_5h_time(time);
		}
		else {
			return get_day_end_time(time);
		}
	}

	static std::string GetDateStr(time_t time)
	{
		tm* ret = localtime(&time);
		char buffer[20] = {0};
		strftime(buffer, 20, "%Y%m%d", ret);
		return std::string(buffer);
	}

	static bool is_same_day(int32_t time1, int32_t time2)
	{
		if (time1 - time2 > DAY_SECS || time2 - time1 > DAY_SECS) {
			return false;
		}
		return (get_day_end_time(time1) == get_day_end_time(time2));
	}

	static void MsgToStr(const google::protobuf::Message * msg, std::string & str)
	{
		std::string serStr;
		msg->SerializeToString(&serStr);

		str.resize(serStr.size() * 2);
		Hexify((unsigned char *)str.c_str(), (unsigned char *)serStr.c_str(),serStr.size());
	}


	//将6:30:00形式的时间转化为当天这个点的时间撮
	static uint32_t GetTimeDayStr(const std::string &fmt)
	{
		time_t sec = time(nullptr);
    	struct tm t;
 	    localtime_r(&sec, &t);
    	auto times = ShareUtils::split(fmt, ':');
    	t.tm_hour = atoi(times[0].c_str());
     	t.tm_min = atoi(times[1].c_str());
     	t.tm_sec = atoi(times[2].c_str());
     	sec = mktime(&t);
     	return sec;	
 	}

	static bool StrToMsg(const char *str, google::protobuf::Message * msg)
	{
		if (str == nullptr)
			return false;
		std::string serStr;
		size_t len = strlen(str);
		if (len < 2)
			return false;

		serStr.resize(len / 2);
		UnHexify((unsigned char *)serStr.c_str(), str);
		return msg->ParseFromString(serStr);
	}
	static const unsigned long MAX_COMPRESS_SIZE = 1024*1024;
	static bool MsgCompressToString(const google::protobuf::Message *msg,std::vector<uint8_t> &destvec)
	{
		static char source[MAX_COMPRESS_SIZE] = {0};         
		static char dest[MAX_COMPRESS_SIZE] = {0};        
		memset(source,0,MAX_COMPRESS_SIZE);
		memset(dest,0,MAX_COMPRESS_SIZE);
		msg->SerializeToArray(source,sizeof(source));
		//std::string str_tmp;
		//google::protobuf::util::MessageToJsonString(*msg,&str_tmp);
		//strcpy((char*)source,str_tmp.c_str());
		unsigned long len = compressBound(strlen(source)+1); 
		unsigned long err = compress((unsigned char*)dest,&len,(unsigned char*)source,strlen(source));
		DEBUG_LOG("[newactivity_zyw] MsgCompressToString err=%lu,source.size=%lu,dest.size=%lu",err,strlen(source),len);
		if(err != Z_OK)
		{
			return false; 
		}
		destvec.insert(destvec.end(),dest,dest+len);
		return true;
	}
	static bool StringUnCompressToMsg(const std::vector<uint8_t> &sourcevec,google::protobuf::Message *msg)
	{
		static char dest[MAX_COMPRESS_SIZE] = {0};        
		memset(dest,0,MAX_COMPRESS_SIZE);
		unsigned long len = MAX_COMPRESS_SIZE;
		unsigned long err = uncompress((unsigned char*)dest,&len,(const unsigned char*)&sourcevec[0],sourcevec.size());
		DEBUG_LOG("[newactivity_zyw] StringUnCompressToMsg err=%lu,source.size=%lu,dest.size=%lu",err,sourcevec.size(),len);
		if(err != Z_OK)
		{
			return false; 
		}
		msg->ParseFromArray(dest,len);
		//std::string str_tmp = dest;
		//google::protobuf::util::JsonStringToMessage(str_tmp,msg);
		return true;
	}

private:
	static inline int split_str_to_items(char* source, std::vector<item_conf_t>& info) {
		char* tmp_p = source;
		char* out_p;
		char* in_p;
		char* tmp_strtok;
		while((tmp_strtok = strtok_r(tmp_p, ";", &out_p)) != NULL) {
			if (!atoi(tmp_strtok)) break;
			item_conf_t item;
			int loop = 0;
			while((tmp_strtok = strtok_r(tmp_p, "/", &in_p)) != NULL) {
				if (loop == 0) item.item_id = atoi(tmp_strtok);
				if (loop == 1) item.cnt = atoi(tmp_strtok);
				++loop;
				tmp_p = in_p;
			}

			//check valid
			if (loop != 2) {
				return -1;
			}
			tmp_p = out_p;
			info.push_back(item);
		}
		return 0;
	}

	static inline int split_str_to_items(std::vector<normal_item_t>& info, char* source) {
		char* tmp_p = source;
		char* out_p;
		char* in_p;
		char* tmp_strtok;
		while((tmp_strtok = strtok_r(tmp_p, ";", &out_p)) != NULL) {
			if (!atoi(tmp_strtok)) break;
			normal_item_t item;
			int loop = 0;
			while((tmp_strtok = strtok_r(tmp_p, "/", &in_p)) != NULL) {
				if (loop == 0) item.id = atoi(tmp_strtok);
				if (loop == 1) item.count = atoi(tmp_strtok);
				++loop;
				tmp_p = in_p;
			}

			//check valid
			if (loop != 2) {
				return -1;
			}
			tmp_p = out_p;
			info.push_back(item);
		}
		return 0;
	}

	static int UnHexify(unsigned char *obuf, const char *ibuf)
	{
		unsigned char c, c2;
		int len = strlen(ibuf) / 2;
		assert(!(strlen(ibuf) % 1)); // must be even number of bytes

		while (*ibuf != 0)
		{
			c = *ibuf++;
			if (c >= '0' && c <= '9')
				c -= '0';
			else if (c >= 'a' && c <= 'f')
				c -= 'a' - 10;
			else if (c >= 'A' && c <= 'F')
				c -= 'A' - 10;
			else
				assert(0);

			c2 = *ibuf++;
			if (c2 >= '0' && c2 <= '9')
				c2 -= '0';
			else if (c2 >= 'a' && c2 <= 'f')
				c2 -= 'a' - 10;
			else if (c2 >= 'A' && c2 <= 'F')
				c2 -= 'A' - 10;
			else
				assert(0);

			*obuf++ = (c << 4) | c2;
		}

		return len;
	}

	static void Hexify(unsigned char *obuf, const unsigned char *ibuf, int len)
	{
		unsigned char l, h;

		while (len != 0)
		{
			h = (*ibuf) / 16;
			l = (*ibuf) % 16;

			if (h < 10)
				*obuf++ = '0' + h;
			else
				*obuf++ = 'a' + h - 10;

			if (l < 10)
				*obuf++ = '0' + l;
			else
				*obuf++ = 'a' + l - 10;

			++ibuf;
			len--;
		}
	}

private:
	static inline int split_str_to_map(char* source, std::map<uint32_t, uint32_t>& info) {
		char* tmp_p = source;
		char* out_p;
		char* in_p;
		char* tmp_strtok;
		while((tmp_strtok = strtok_r(tmp_p, ";", &out_p)) != NULL) {
			if (!atoi(tmp_strtok)) break;
			item_conf_t item;
			int loop = 0;
			while((tmp_strtok = strtok_r(tmp_p, "/", &in_p)) != NULL) {
				if (loop == 0) item.item_id= atoi(tmp_strtok);
				if (loop == 1) item.cnt = atoi(tmp_strtok);
				++loop;
				tmp_p = in_p;
			}

			//check valid
			if (loop != 2) {
				return -1;
			}
			tmp_p = out_p;
			info.insert(std::map<uint32_t, uint32_t>::value_type(item.item_id, item.cnt));
		}
		return 0;
	}

public:
	/* @brief 解析配置表中物品字段使用的函数，解析格式"物品id/物品个数;循环"
	*/
	static inline int parser_items(xmlNodePtr cur, const char* name, std::vector<item_conf_t>& info)
	{
		char src[1000];
		memset(src, 0, sizeof(src));
		taomee::get_xml_prop_raw_str_def(src, cur, name, "");

		int ret = split_str_to_items(src, info);
		if(ret) {
			KERROR_LOG(0, "%s err", name);
		}
		return ret;
	}

	static inline int parser_items_map(xmlNodePtr cur, const char* name, std::map<uint32_t, uint32_t>& info)
	{
		char src[1000];
		memset(src, 0, sizeof(src));
		taomee::get_xml_prop_raw_str_def(src, cur, name, "");

		int ret = split_str_to_map(src, info);
		if(ret) {
			KERROR_LOG(0, "%s err", name);
		}
		return ret;
	}

	static inline int parser_items(std::vector<normal_item_t>& info, xmlNodePtr cur, const char* name)
	{
		char src[1000];
		memset(src, 0, sizeof(src));
		taomee::get_xml_prop_raw_str_def(src, cur, name, "");

		int ret = split_str_to_items(info, src);
		if(ret) {
			KERROR_LOG(0, "%s err", name);
		}
		return ret;
	}

	static inline int replace_dirty_msg(const std::string& original_msg,
			std::string& replace_msg)
	{
		char* cmsg = new char[original_msg.length() + 1];
		strcpy(cmsg, original_msg.c_str());
		int ret = tm_dirty_replace(cmsg);
		replace_msg = cmsg;
		delete cmsg;
		return ret;
	}

	/** 
	 * @brief  从[begin,end]中随机挑选出n个数
	 *
	 * @param begin 起始数
	 * @param end 终止数
	 * @param n 选出n个
	 * @param list 保存选出的数，从小到大有序排列
	 *
	 * @return 0 成功 -1失败
	 */
	static inline void select_n_from_m(uint32_t begin, uint32_t end, 
			uint32_t n, std::vector<uint32_t>& list) {

		if (begin + n >= end + 1) {
			return;
		}   

		if (n == 0) {
			return ;
		}   

		uint32_t remain = end - begin + 1;
		uint32_t total = remain;
		uint32_t sel = n;
		for (uint32_t i = 0; i < total; ++i) {
			uint32_t rand = taomee::ranged_random(1, remain);
			if (rand <= sel) {
				list.push_back(begin + i); 
				--remain;
				--sel;
			} else {
				--remain;
			}   
			if (sel == 0) {
				break;
			}   
		}
	}

	static inline void select_n_from_vec(std::vector<uint32_t>& vec_source, 
			uint32_t n, std::vector<uint32_t>& vec_result)
	{
		if (vec_source.size() == 0 || n >= vec_source.size()) {
			vec_result = vec_source;
			return ;
		}

		uint32_t size = vec_source.size();
		for (uint32_t i=0; i < n; i++) {
			if (size == 1) {
				vec_result.push_back(vec_source[size-1]);
				return ;
			}
			uint32_t rand = taomee::ranged_random(0, size-1);
			vec_result.push_back(vec_source[rand]);
			if (rand != size-1) {
				vec_source[rand] = vec_source[size-1];
			}
			size--;
		}
	}

    static void sha256(const std::string &srcStr, std::string &encodedStr, std::string &encodedHexStr)  
    {  
	    // 调用sha256哈希    
	    unsigned char mdStr[33] = {0};  
	    SHA256((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);  

	    // 哈希后的字符串    
	    encodedStr = std::string((const char *)mdStr);  
	    // 哈希后的十六进制串 32字节    
	    char buf[65] = {0};  
	    char tmp[3] = {0};  
	    for (int i = 0; i < 32; i++)  
	    {  
		    sprintf(tmp, "%02x", mdStr[i]);  
		    strcat(buf, tmp);  
	    }  
	    buf[32] = '\0'; // 后面都是0，从32字节截断    
	    encodedHexStr = std::string(buf);  
    }  

    static void sha1(const std::string &srcStr, std::string &encodedStr, std::string &encodedHexStr)  
    {  
	    // 调用sha1哈希    
	    unsigned char mdStr[SHA_DIGEST_LENGTH+1];
	    SHA1((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);  

	    // 哈希后的字符串    
	    encodedStr = std::string((const char *)mdStr);  
	    std::stringstream oss;
	    char tmp[3] = {0};  
	    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)  
	    {  
		    sprintf(tmp, "%02x", mdStr[i]);  
		    oss << tmp;
	    }  
	    encodedHexStr = oss.str();  
    }  

    static RSA* createRSA(unsigned char*key,int publi) {    
    	RSA *rsa= NULL;    
    	BIO*keybio ;    
    	keybio= BIO_new_mem_buf(key, -1);   
    	if(keybio==NULL) 
    	{       
    		ERROR_LOG("Failed to create key BIO");    
    		return 0;   
    	}
    
    	if(publi)
    	{    
    		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);   
    	}
    	else   
    	{    
    		rsa= PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL); 
    	}           
    	if(rsa== NULL)    
    	{        
    		ERROR_LOG("Failed to create RSA");    
    	}      
    	return rsa;
    } 
    
    static void GetRealPlatformIdAndSession(int platformId, const std::string& session,
            int& realPlatformId, std::string& realSession) {
        if (platformId == PLATFORM_ANDROID_YINGYONGBAO) {
            std::string keyStr = session.substr(0, 2);
    		if(keyStr == "QQ") {
    			realPlatformId = PLATFORM_ANDROID_YINGYONGBAO * 10;
                realSession = session;
    		}
    		else if(keyStr == "WX") {
    			realPlatformId = PLATFORM_ANDROID_YINGYONGBAO * 10 + 1;
                realSession = session;
    		}
    	} else if (platformId == PLATFORM_ANDROID_YJM) {
            std::string keyStr = session.substr(0, 3);
            if (keyStr == "GOO") {
                // GOOGLE
                realPlatformId = PLATFORM_ANDROID_YJM * 10;
                realSession = session.substr(7, session.length() - 7);
            } else if (keyStr == "FAC") {
                // FACEBOOK
                realPlatformId = PLATFORM_ANDROID_YJM * 10 + 1;
                realSession = session.substr(9, session.length() - 9);
            } else if (keyStr == "AUT") {
                // AUTO
                auto vec = ShareUtils::Split(session, '-');
                if (vec.size() == 3) {
                    if (vec[2] == "GOOGLE") {
                        realPlatformId = PLATFORM_ANDROID_YJM * 10;
                    } else {
                        realPlatformId = PLATFORM_ANDROID_YJM * 10 + 1;
                    }
                } else {
                    realPlatformId = PLATFORM_ANDROID_YJM * 10;
                }

                realSession = session;
            }
    	} else if (platformId == PLATFORM_ONESTORE_YJM) {
            std::string keyStr = session.substr(0, 3);
            if (keyStr == "GOO") {
                // GOOGLE
                realPlatformId = PLATFORM_ONESTORE_YJM * 10;
                realSession = session.substr(7, session.length() - 7);
            } else if (keyStr == "FAC") {
                // FACEBOOK
                realPlatformId = PLATFORM_ONESTORE_YJM * 10 + 1;
                realSession = session.substr(9, session.length() - 9);
            } else if (keyStr == "AUT") {
                // AUTO
                auto vec = ShareUtils::Split(session, '-');
                if (vec.size() == 3) {
                    if (vec[2] == "GOOGLE") {
                        realPlatformId = PLATFORM_ONESTORE_YJM * 10;
                    } else {
                        realPlatformId = PLATFORM_ONESTORE_YJM * 10 + 1;
                    }
                } else {
                    realPlatformId = PLATFORM_ONESTORE_YJM * 10;
                }

                realSession = session;
            }
		} else if (platformId == PLATFORM_SAMSUNG_YJM) {
			std::string keyStr = session.substr(0, 3);
			if (keyStr == "GOO") {
				// GOOGLE
				realPlatformId = PLATFORM_SAMSUNG_YJM * 10;
				realSession = session.substr(7, session.length() - 7);
			} else if (keyStr == "FAC") {
				// FACEBOOK
				realPlatformId = PLATFORM_SAMSUNG_YJM * 10 + 1;
				realSession = session.substr(9, session.length() - 9);
			} else if (keyStr == "AUT") {
				// AUTO
				auto vec = ShareUtils::Split(session, '-');
				if (vec.size() == 3) {
					if (vec[2] == "GOOGLE") {
						realPlatformId = PLATFORM_SAMSUNG_YJM * 10;
					} else {
						realPlatformId = PLATFORM_SAMSUNG_YJM * 10 + 1;
					}
				} else {
					realPlatformId = PLATFORM_SAMSUNG_YJM * 10;
				}
				realSession = session;
			}
		} else if (platformId == PLATFORM_IOS_YJM) {
            std::string keyStr = session.substr(0, 3);
            if (keyStr == "GUE") {
                // GUEST
                realPlatformId = PLATFORM_IOS_YJM * 10;
                realSession = session.substr(6, session.length() - 6);
            } else if (keyStr == "GAM") {
                // GAMECENTER
                realPlatformId = PLATFORM_IOS_YJM * 10 + 1;
                realSession = session.substr(11, session.length() - 11);
            } else if (keyStr == "GOO") {
                // GOOGLE
                realPlatformId = PLATFORM_IOS_YJM * 10 + 2;
                realSession = session.substr(7, session.length() - 7);
            } else if (keyStr == "FAC") {
                // FACEBOOK
                realPlatformId = PLATFORM_IOS_YJM * 10 + 3;
                realSession = session.substr(9, session.length() - 9);
            } else if (keyStr == "AUT") {
                // AUTO
                auto vec = ShareUtils::Split(session, '-');
                if (vec.size() == 3) {
                    if (vec[2] == "GUEST") {
                        realPlatformId = PLATFORM_IOS_YJM * 10;
                    } else if (vec[2] == "GAMECENTER") {
                        realPlatformId = PLATFORM_IOS_YJM * 10 + 1;
                    } else if (vec[2] == "GOOGLE") {
                        realPlatformId = PLATFORM_IOS_YJM * 10 + 2;
                    } else {
                        realPlatformId = PLATFORM_IOS_YJM * 10 + 3;
                    }
                } else {
                    realPlatformId = PLATFORM_IOS_YJM * 10 + 2;
                }
                realSession = session;
            }
        } else {
            realPlatformId = platformId;
            realSession = session;
        }
    }

        template<typename T>
        static T clamp(T x, T a, T b) {
            return fmin(fmax(x, a), b);
        }


    static std::vector<std::string> Split(const std::string& s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);

        if (s == "") {
            return tokens;
        }

        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }

        if (s.back() == delimiter) {
            tokens.push_back("");
        }

        return tokens;
    }
};

#endif
