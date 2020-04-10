#encoding=utf-8
import codecs
import json
from database import Database
from utility import getGameTableName
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

def joinNumberArray(array):
    text = ''
    for i in range(len(array)):
        if i > 0:
            text = text + ","
        text = text + str(array[i])
    return text


def processAll():
    source = 5;
    serverIds = [601,602] 

    serverIdsText = joinNumberArray(serverIds)
    sqlstr = 'select userid, nick,original_server_id from t_isg_account_info where server_id in (' + serverIdsText + ');'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            osrvid = record['original_server_id']
            tableName = getGameTableName('user_info',userId)
            sqlstr = 'update ' + tableName +' set nick= CONCAT(nick, + "_'+str(osrvid)+'"),title = 0 where id=' + str(userId) + ';'
            print(sqlstr)
            logging.info(u'info 信息:sql:' + sqlstr)
            gameDb.execute(sqlstr, userId)
            
    #清理首次占领城池奖励的标识
    sqlstr = 'select userid from t_isg_account_info where server_id in (' + serverIdsText + ')'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            tableName = getGameTableName('user_attr',userId)
            sqlstr = 'delete from ' + tableName + ' where userid=' + str(userId) + ' and `key`>=121000 and `key`<=121300'
            print(sqlstr)
            logging.info(u'info 信息:' + sqlstr)
            gameDb.execute(sqlstr, userId)
    

processAll()
gameDb.closeAll()
accountDb.closeAll()
