#encoding=utf-8
import codecs
import json
from database import Database
from utility import getGameTableName
import re
import logging
import sys
reload(sys)
sys.setdefaultencoding('utf8')

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



def processAll():
    
    sqlstr = 'select userid from t_isg_account_info'
    print(sqlstr)
    records = accountDb.queryAll(sqlstr)
    if records <> None:
        for i in range(len(records)):
            record = records[i]
            userId = record['userid']
            tableName = getGameTableName('user_newactivity',userId)
            sqlstr = 'select userid,datajsonstr  from ' + tableName + ' where type = 31 and userid = ' + str(userId)  + ' and id in (1633,1641)'
            print(sqlstr)
            datas = gameDb.queryAll(sqlstr,userId)
            if datas <> None:
                for j in range(len(datas)):
                    data = datas[j]
                    uid = data['userid']
                    strvalue = data['datajsonstr']
                    jdata = json.loads(strvalue)
                    if jdata['wishdata'] <> None:
                        for l in range(len(jdata['wishdata'])):
                            if jdata['wishdata'][l].has_key('wishawardid') and not jdata['wishdata'][l].has_key('isget'):
                                print(str(jdata['wishdata'][l]['wishawardid']))
                                logging.info(u'userid:' + str(uid) + u',' + 'wishawardid:' + str(jdata['wishdata'][l]['wishawardid']))



processAll()

gameDb.closeAll()
accountDb.closeAll()
