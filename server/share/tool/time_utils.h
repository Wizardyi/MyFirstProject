#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <stdint.h>

//定义一天有多少秒 正常是86400
#define DAY_SECS (86400)
#define DAY_ADJ (57600)

class TimeUtils 
{
	public:
		// static bool is_same_day(int32_t time1, int32_t time2);

		static int second_at_day_start(int32_t day_offset);
		
		static uint32_t time_to_date(time_t time);

		// 获取当天结束时候的时间戳
		// 因为业务需要，游戏中每一天从当天自然时间凌晨5点开始
		// 到第二天自然时间凌晨5点结束 
		// static time_t get_day_end_time(time_t time);
};

#endif
