#ifndef __TIMER_PROCS_H__
#define __TIMER_PROCS_H__

#include "share/module/common.h"

enum timer_type_t {
    kTimerTypeReconnectServiceTimely        = 1, // 重连service服务器
	kTimerTypeDetectionServiceTimely		= 2, // 检测服务器是否存在
};

enum timer_interval_t {
    kTimerIntervalReconnectServiceTimely    = 1, // 重连service服务器间隔
	kTimerIntervalDetectionServiceTimely	= 70, // 检测服务器是否存在的时间间隔
};

struct timer_head_t {
    list_head_t timer_list;
};

int register_timers();

extern timer_head_t g_reconnect_timer;

#endif
