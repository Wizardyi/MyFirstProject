#encoding=utf-8
_GAME_LOG_TABLE = (
        "log_user_login",
        "log_user_logout",
        "log_add_award",
        "log_national_quest",
        "log_add_hero",
        "log_del_hero",
        "log_hero_level_up",
        "log_add_res",
        "log_expend_res",
        "log_add_exp",
        "log_add_item",
        "log_expend_item",
        "user_world_war_exploit",
        "log_register",
        "log_pay_record",
        "log_buy_item",
        "log_pvp_battle",
        "log_add_equip",
        "log_starup_equip",
        "log_levelup_equip",
        "log_reset_equip",
        "log_del_equip",
        "log_event_type",
        "log_new_guide",
        "log_set_nick",
        "log_hero_add_exp",
        "log_hero_event_type",
        "log_user_chat",
        "log_newactivity_act")

_GAME_TABLE_COUNT = {
        'guild_apply_info' : 10,
        'guild_member_info' : 10,
        'team_cluster' : 10,
        'user_attr' : 100,
        'user_battle' : 100,
        'user_biography' : 10,
        'user_contact' : 10,
        'user_cycle_battle' : 10,
        'user_dispatch_team' : 10,
        'user_equip' : 100,
        'user_friend' : 100,
        'user_gift_code' : 10,
        'user_guild_info' : 10,
        'user_hero' : 100,
        'user_info' : 10,
        'user_item' : 100,
        'user_littlewar' : 100,
        'user_mail' : 100,
        'user_quest' : 100,
        'user_resource' : 100,
        'user_shared_quest' : 10,
        'user_shop' : 10,
        'user_newactivity' : 10
        }
def getGameTableName(tableName, userId):
    if _GAME_TABLE_COUNT.has_key(tableName):
        tableCount = _GAME_TABLE_COUNT[tableName]
        tableIndex = ((userId - (userId % 100)) / 100) % 100
        suffix = str(tableIndex).zfill(2)
        if tableCount == 10:
            tableIndex = (tableIndex - (tableIndex % 10)) / 10
            suffix = str(tableIndex)
        return tableName + '_' + suffix
    return tableName

