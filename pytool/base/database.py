#encoding=utf-8
import pymysql

class DbInfo:
    def __init__(self, id, host, port, user, password, dbName):
        self.id = id
        self.host = host
        self.port = port
        self.user = user
        self.password = password
        self.dbName = dbName
        self.connection = None
    def getConnection(self):
        if ( self.connection == None ):
            self.connection = pymysql.connect(host=self.host, port=self.port, user=self.user, passwd=self.password, db=self.dbName)
        return self.connection
    def close(self):
        if ( self.connection != None ):
            self.connection.close()
            self.connection = None

class Database:
    def __init__(self, shardingCount):
        self.allDb = None
        self.shardingCount = shardingCount

    def addShardingDb(self, dbPrefix, host, port, user, password, minSuffix, maxSuffix):
        if self.shardingCount <= 1:
            print(u"该连接池中不支持分库配置!")
            return
        if self.allDb == None:
            self.allDb = {}

        for i in range(minSuffix, maxSuffix) :
            dbName = dbPrefix + str(i).zfill(2)
            newInstance = DbInfo(i, host, port, user, password, dbName)
            if ( self.allDb.has_key(i) ):
                print(u"发现重复的数据库:" + dbName)
                return
            else:
                self.allDb[i] = newInstance
    def addSingleDb(self, host, port, user, password, dbName):
        if self.shardingCount > 1:
            print(u"该连接池使用了分库配置!")
            return
        if self.allDb == None:
            self.allDb = DbInfo(-1, host, port, user, password, dbName)
    def getConnection(self, shardingId=None):
        if self.allDb <> None:
            if self.shardingCount > 1:
                dbIndex = shardingId % self.shardingCount
                if ( self.allDb.has_key(dbIndex) ):
                    return self.allDb[dbIndex].getConnection()
            else:
                return self.allDb.getConnection()
        return None
        
    def closeAll(self):
        if self.allDb <> None:
            if self.shardingCount > 1:
                for i in self.allDb:
                    self.allDb[i].close()
            else:
                self.allDb.close()
            self.allDb = None

    def queryOne(self, sql, shardingId = None):
        connection = self.getConnection(shardingId)
        cursor = connection.cursor(cursor=pymysql.cursors.DictCursor)
        try:
            cursor.execute(sql)
            record = cursor.fetchone()
        except Exception as e:
            record = None
        cursor.close()
        return record
    def queryAll(self, sql, shardingId = None):
        connection = self.getConnection(shardingId)
        cursor = connection.cursor(cursor=pymysql.cursors.DictCursor)
        try:
            cursor.execute(sql)
            records = cursor.fetchall()
        except Exception as e:
            print(e)
            records = None
        cursor.close()
        return records
    def execute(self, sql, shardingId = None):
        connection = self.getConnection(shardingId)
        cursor = connection.cursor(cursor=pymysql.cursors.DictCursor)
        try:
            cursor.execute(sql)
            connection.commit()
        except Exception as e:
            pass
        cursor.close()
        
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
    'user_shop' : 10
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