#include<time.h>
extern "C" {
#include <libtaomee/log.h>
#include <libtaomee/timer.h>
}

#include "macro_utils.h"
#include "time_utils.h"
#include "share/size_df.h"

// bool TimeUtils::is_same_day(int32_t time1, int32_t time2)
// {
// 	if (time1 - time2 > DAY_SECS || time2 - time1 > DAY_SECS) {
// 		return false;
// 	}   
// // 	struct tm date1, date2;
// // 	time_t tm1 = time1;
// // 	time_t tm2 = time2;
// // 	localtime_r(&tm1, &date1);
// // 	localtime_r(&tm2, &date2);
// // 	return (date1.tm_mday == date2.tm_mday);
// 	return (get_day_end_time(time1) == get_day_end_time(time2));
// }

int TimeUtils::second_at_day_start(int32_t day_offset) {
	static int today_start = 0;
	static uint32_t cur_date = 0;  

	struct tm now;
	time_t now_sec = NOW();
	localtime_r(&now_sec, &now);
	uint32_t now_date = time_to_date(now_sec);
	if (cur_date != now_date) {
		cur_date = now_date;
		now.tm_hour = 0;
		now.tm_min = 0;
		now.tm_sec = 0;
		today_start = mktime(&now); 
	}   

	return today_start + (day_offset * DAY_SECS);
}

uint32_t TimeUtils::time_to_date(time_t time)
{
    tm tm;
    localtime_r(&time, &tm);

    return (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
}

// time_t TimeUtils::get_day_end_time(time_t time)
// {
// 	struct tm date;
// 	localtime_r(&time, &date);
// 	if (date.tm_hour < DAY_START_TIME) {
// 		date.tm_hour = DAY_START_TIME;
// 		date.tm_min = 0;
// 		date.tm_sec = 0;
// 		return mktime(&date);
// 	}
// 	else {
// 		date.tm_hour = DAY_START_TIME;
// 		date.tm_min = 0;
// 		date.tm_sec = 0;
// 		return mktime(&date) + DAY_SECS;
// 	}
// }
// 
