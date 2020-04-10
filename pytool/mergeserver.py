#encoding=utf-8
import codecs
import json
from database import Database
from redisClient import Redis
import re
import sys
import logging
logging.basicConfig(level=logging.DEBUG,
                    filename='new.log',
                    filemode='a',
                    format=
                    '%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s'
                    )

accountDb = Database(1)
accountDb.addSingleDb('192.168.2.235', 3306, 'inksg', 'isg@mysql', 'ISG_ACCOUNT')
cache = Redis('192.168.2.232', 6379, 0, '')


serverIds = [601,602]

uids = []

mergeServerId = 1901
mergeUid = ((5 << 32) | mergeServerId);
sameId = 0;

cityids = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,
            101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,
            121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159]



def checkSameId():
    have = False
    uidText = joinNumberArray(uids)
    sql = 'SELECT id,COUNT(id) from  guild_info GROUP BY id'
    print(sql)
    records = accountDb.queryAll(sql)
    for i in range(len(records)):
        record = records[i]
        if  int(record['COUNT(id)']) > 1:
            have = True;
            global sameId;
            sameId = int(record['id'])
            print(have,sameId)
    return have
                


def joinNumberArray(array):
    text = ''
    for i in range(len(array)):
        if i > 0:
            text = text + ","
        text = text + str(array[i])
    return text
    
    
def getUids():
    for i in range(len(serverIds)):
        serverid = serverIds[i]
        uid = ((5 << 32) | serverid)
        uids.append(uid)
    

def processMerge():
    uidText = joinNumberArray(uids)
    sql = 'update guild_info set uid = ' +  str(mergeUid) + '  where uid in (' + uidText + ')'   
    print(sql)
    accountDb.execute(sql)
    serverText = joinNumberArray(serverIds)
    sql = 'update t_isg_account_info set server_id = ' +  str(mergeServerId) + '  where server_id in (' + serverText + ')'
    print(sql)
    logging.info(u'info 信息:sql:' + sql)
    accountDb.execute(sql)
    
  
    #清理边境守卫军城市数据,城市国战数据
    source = 5
    for i in serverIds:
        sourceserver = str(source)+':'+str(i)
        rediskey = sourceserver+':border'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)
        
        for l in cityids:
            rediskey = sourceserver+':' + str(l) + ':border_user_rank'
            print(rediskey)
            logging.info(u'info 信息:rediskey:' + rediskey)
            cache.delete(rediskey)
        for l in cityids:       
            rediskey = sourceserver+':' + str(l) + ':border_guild_rank'
            print(rediskey)
            logging.info(u'info 信息:rediskey:' + rediskey)
            cache.delete(rediskey)
        rediskey = sourceserver+':world_war_simple_info'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)               
        rediskey = sourceserver+':world_war_application_info'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)                 
        
        rediskey = sourceserver+':dispatch_team'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)                 
        rediskey = sourceserver+':force_resource'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)
        #重置玩家官职竞选数据
        rediskey = sourceserver+':title_election_info'
        print(rediskey)
        logging.info(u'info 信息:rediskey:' + rediskey)
        cache.delete(rediskey)
    
    

def processAll():
    if  checkSameId() and sameId != 0:
        print('the same id:' + str(sameId))
        sys.exit(1)
    getUids()
    processMerge()
    print('success')
    
    
processAll()

accountDb.closeAll()