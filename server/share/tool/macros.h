#pragma once

#define DEFINE_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: varType Get##funName(void) const { return varName; }\
public: void Set##funName(varType var){ varName = var; }

#define DEFINE_PROPERTY_REF(varType, varName, funName)\
protected: varType varName;\
public: varType& Get##funName(void) { return varName; }\
public: void Set##funName(const varType& var){ varName = var; }

#define DEFINE_STATIC_UID(varType, varName)\
protected: static varType varName;\
public: static varType GenerateUID(void) { varName++; return varName;}\
public: static void SetUID(const varType& var){ varName = var; }

#define DEFINE_STATIC_PRO_REF(varType, varName, funName)\
protected: static varType varName;\
public: static varType& Get##funName(void) { return varName; }\
public: static void Set##funName(const varType& var){ varName = var; }

#define sanguo_max(a,b) (((a) > (b)) ? (a) : (b))
#define sanguo_min(a,b) (((a) < (b)) ? (a) : (b))

#define GET_A(player, type) \
    AttrUtils::get_attr_value(player, type)

#define SET_A(player, type, value) \
    RETURN_ERR(AttrUtils::set_single_attr_value(player, type, value))

#define ADD_A(player, type, value) \
    RETURN_ERR(AttrUtils::add_attr_value(player, type, value))

#define MINUS_A(player, type, value) \
    RETURN_ERR(AttrUtils::minus_attr_value(player, type, value))

#define CHECK_A(player, type, value) do { uint32_t old_value = GET_A(player, type); if (old_value >= value) { } else { return cli_err_lack_usable_item; } } while (0)
        
//idx从0开始
#define SET_BIT(player, type, idx) do { std::bitset<32> bit(GET_A(player, type)); bit.set(idx);SET_A(player, type, bit.to_ulong());} while (0) 

#define RISETO_A(player, type, value) do { if (GET_A(player, type) < value) { SET_A(player, type, value);}} while (0)

#define FOREACH(container, it) \
    for(auto it=(container).begin(); it!=(container).end(); ++it)

#define FOREACH_PTR(container, it) \
    for(auto it=(container)->begin(); it!=(container)->end(); ++it)

#define REVERSE_FOREACH(container, it) \
    for(auto it=(container).rbegin(); it!=(container).rend(); ++it)

#define FOREACH_NOINCR_ITER(container, it) \
       for(auto it=(container).begin(); it!=(container).end();) 

#define REVERSE_FOREACH_NOINCR_ITER(container, it) \
        for(auto it=(container).rbegin(); it!=(container).rend();)

//必须在setup_timer之后才能使用
#define NOW()   (get_now_tv()->tv_sec)

#define RETURN_ERR(func) do { int ret = func; if (ret) return send_default_cmd_err(player, ret);} while(0)

#define INIT_REASON(CLASS) \
    CLASS(uint32_t last_battle_tm_type, uint32_t cd, uint32_t daily_count_type, uint32_t count, uint32_t daily_buy_count_type = 0, bool cd_is_check_vip_type = false, bool count_is_check_vip_type = false, uint32_t monsterid = 0) : BattleVsMonsterCommonReason(last_battle_tm_type, cd, daily_count_type, count, daily_buy_count_type, cd_is_check_vip_type, count_is_check_vip_type, monsterid)\
{ \
}; 


#define ERR_CHAIN(func) do { int ret = func; if (ret) return ret;} while(0)

#define ZERO_CHAIN(func) do { int ret = func; if (ret) return 0;} while(0)

// 字符串赋值(字符串->字符串)
#define SNPRINTF_ATOA(dst, src)     snprintf(dst, sizeof(dst), "%s", src);

