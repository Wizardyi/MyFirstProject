#pragma once

#include <chrono>

#include "share/tool/macros.h"

class CTroop
{
	public:
		CTroop() {
			troop_id_ = 0;
			attack_ = 0.00f;
			hp_ = 0.00f;
			cd_ = 1000; // ms
			offensive_ = 0;
		}
		~CTroop() {

		}

		DEFINE_PROPERTY(uint64_t, troop_id_, TroopID);	// 部队ID 
		DEFINE_PROPERTY(float, attack_, Attack);		// 部队攻击力
		DEFINE_PROPERTY(float, hp_, HP);				// 部队血量
		DEFINE_PROPERTY(uint32_t, cd_, CD);				// 战斗CD 单位毫秒
		DEFINE_PROPERTY(uint32_t, offensive_, Offensive); // 先手值
		DEFINE_PROPERTY(std::chrono::time_point<std::chrono::high_resolution_clock>, fight_time_, FightTime); // 上次战斗时间
};

