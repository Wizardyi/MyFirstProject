#encoding=utf-8
import codecs
import json
from redisClient import Redis
from database import Database
from utility import getGameTableName
import re
import logging
logging.basicConfig(level=logging.DEBUG,
                    filename='new.log',
                    filemode='a',
                    format=
                    '%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s'
                    )

gameDb = Database(100)
gameDb.addShardingDb("ISG_", "192.168.2.235", 3306, "inksg", "isg@mysql", 0, 41)
gameDb.addShardingDb("ISG_", "192.168.2.232", 3306, "inksg", "isg@mysql", 41, 100)

accountDb = Database(1)
accountDb.addSingleDb('192.168.2.235', 3306, 'inksg', 'isg@mysql', 'ISG_ACCOUNT')
cache = Redis('192.168.2.232', 6379, 0, '')

def joinNumberArray(array):
    text = ''
    for i in range(len(array)):
        if i > 0:
            text = text + ","
        text = text + str(array[i])
    return text

def processAll():
    source = 5;
    serverIds = [30001]    #要重置的serverid
    
    #清理天下大势表
    serverIdsText = joinNumberArray(serverIds)
    sqlstr = 'delete from the_world_achievement_event where server_id in (' + serverIdsText + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    sqlstr = 'delete from the_world_force_achievement where server_id in (' + serverIdsText + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    sqlstr = 'delete from the_world_trend where server_id in (' + serverIdsText + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)

    uidstext = ''
    for i in range(len(serverIds)):
        if i > 0:
            uidstext = uidstext + ","
        uidstext = uidstext + str(serverIds[i]|(source<<32))

    #清理城市数据
    sqlstr = 'delete from user_hero_class where uid in (' + uidstext + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    sqlstr = 'delete from user_world_city where uid in (' + uidstext + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    sqlstr = 'delete from user_force where uid in (' + uidstext + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    #清理军团数据
    sqlstr = 'delete from guild_info where uid in (' + uidstext + ')'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    #修改玩家nick
    sqlstr = 'UPDATE t_isg_account_info a INNER JOIN (SELECT userid, CONCAT(nick,"_",server_id) as new_nick FROM t_isg_account_info) b SET a.nick = b.new_nick WHERE a.userid = b.userid and a.server_id in (' + serverIdsText + ');'
    print(sqlstr)
    logging.info(u'info 信息:' + sqlstr)
    accountDb.execute(sqlstr)
    

    #清理军团城市数据
    for i in range(len(serverIds)):
        uid = str(serverIds[i]|(source<<32))
        rediskey = str(uid)+"_*_contribution"
        print(rediskey)
        keys = cache.keys(rediskey)
        if keys <> None:
            for j in keys:
                print(j)
                logging.info(u'del rediskey:' + j)
                cache.delete(j)
        rediskey = str(uid)+"_*_control"
        print(rediskey)
        keys = cache.keys(rediskey)
        if keys <> None:
            for j in keys:
                print(j)
                logging.info(u'del rediskey:' + j)                
                cache.delete(j)
        rediskey = str(uid)+"_*_award"
        print(rediskey)
        keys = cache.keys(rediskey)
        if keys <> None:
            for j in keys:
                print(j)
                logging.info(u'del rediskey:' + j)                
                cache.delete(j)
    
    #清理边境守卫军城市数据,城市国战数据
    for i in serverIds:
        sourceserver = str(source)+':'+str(i)
        rediskey = sourceserver+':border'
        print(rediskey)
        cache.delete(rediskey)
        rediskey = sourceserver+':*:border_user_rank'
        print(rediskey)
        keys = cache.keys(rediskey)
        if keys <> None:
            for j in keys:
                print(j)
                logging.info(u'del rediskey:' + j)
                cache.delete(j)
        rediskey = sourceserver+':*:border_guild_rank'
        print(rediskey)
        keys = cache.keys(rediskey)
        if keys <> None:
            for j in keys:
                print(j)
                logging.info(u'del rediskey:' + j)
                cache.delete(j)
        rediskey = sourceserver+':world_war_simple_info'
        print(rediskey)
        logging.info(u'del rediskey:' + rediskey)
        cache.delete(rediskey)               
        rediskey = sourceserver+':world_war_application_info'
        print(rediskey)
        logging.info(u'del rediskey:' + rediskey)
        cache.delete(rediskey)                 
        
        rediskey = sourceserver+':dispatch_team'
        print(rediskey)
        logging.info(u'del rediskey:' + rediskey)
        cache.delete(rediskey)                 
        rediskey = sourceserver+':force_resource'
        print(rediskey)
        logging.info(u'del rediskey:' + rediskey)
        cache.delete(rediskey)
        #重置玩家官职竞选数据
        rediskey = sourceserver+':title_election_info'
        print(rediskey)
        logging.info(u'del rediskey:' + rediskey)
        cache.delete(rediskey)
         
        
    #重置玩家数据
    serverIdsText = joinNumberArray(serverIds)
    sqlstr = 'select userid from t_isg_account_info where server_id in (' + serverIdsText + ');'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            tableName = getGameTableName('user_info',userId)
            sqlstr = 'update ' + tableName +' set new_guide = 0,city = 8,`force` = 0,title = 0 where id=' + str(userId) + ';'
            print(sqlstr)
            logging.info(u'info 信息:' + sqlstr)
            gameDb.execute(sqlstr, userId)

    
    
    #清理天下大势身上的标识
    sqlstr = 'select userid, nick, server_id, register_time, device_id from t_isg_account_info where server_id in (' + serverIdsText + ')'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            tableName = getGameTableName('user_attr',userId)
            sqlstr = 'delete from ' + tableName + ' where userid=' + str(userId) + ' and `key`>=121301 and `key`<=122500'
            print(sqlstr)
            logging.info(u'info 信息:' + sqlstr)
            gameDb.execute(sqlstr, userId)


processAll()

gameDb.closeAll()
accountDb.closeAll()
