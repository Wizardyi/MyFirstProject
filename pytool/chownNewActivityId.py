#encoding=utf-8
import codecs
import json
from redisClient import Redis
from database import Database
from utility import getGameTableName
import re

#玩家百库百表
gameDb = Database(100)
gameDb.addShardingDb("ISG_", "192.168.2.235", 3306, "inksg", "isg@mysql", 0, 41)
gameDb.addShardingDb("ISG_", "192.168.2.232", 3306, "inksg", "isg@mysql", 41, 100)

#公共库
accountDb = Database(1)
accountDb.addSingleDb('192.168.2.235', 3306, 'inksg', 'isg@mysql', 'ISG_ACCOUNT')

def joinNumberArray(array):
    text = ''
    for i in range(len(array)):
        if i > 0:
            text = text + ","
        text = text + str(array[i])
    return text

def processAll():
    source = 5;
    #需要替换的区id
    serverIds = [23,13]    #zyw
    #需要替换的卡活动id
    chnewactivityids = {
            1122:2129,
            2736:2737,
            2738:2739,
            };
    #替换成后的卡活动版本号
    chnewactivityversion = {
            2129:4,
            2737:1,
            2739:1,
            };

    serverIdsText = joinNumberArray(serverIds)
    sqlstr = 'select userid, nick, server_id from `t_isg_account_info` where `server_id` in (' + serverIdsText + ')'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            tableName = getGameTableName('user_newactivity',userId)
            for key in chnewactivityids:
                sqlstr = 'update ' + tableName +' set `id`='+ str(chnewactivityids[key]) + ',version=' + str(chnewactivityversion[chnewactivityids[key]])+' where `userid`= ' + str(userId) + ' and `id`='+str(key)
                print(sqlstr)
                gameDb.execute(sqlstr, userId)

processAll()

gameDb.closeAll()
accountDb.closeAll()
