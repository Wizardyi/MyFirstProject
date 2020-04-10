#encoding=utf-8
import redis

class Redis:
    def __init__(self, host, port, db, password):
        if password <> None:
            self.connection = redis.Redis(host=host,port=port,db=db,password=password)
        else:
            self.connection = redis.Redis(host=host,port=port,db=db)
        self.hsetKeys = {}
    def hset(self, key, field, value):
        self.connection.hset(key, field, value)
        if not self.hsetKeys.has_key(key):
            self.hsetKeys[key] = 1
    def hlen(self, key):
        return self.connection.hlen(key)
    def hget(self, key, field):
        return self.connection.hget(key, field)
    def incr(self, key, num):
        return self.connection.incr(key, num)
    def get(self, key):
        return self.connection.get(key)
    def set(self, key, value):
        self.connection.set(key,value)
    def zrank(self, key, field):
        return self.connection.zrank(key, field)
    def getInt(self, key):
        result = self.connection.get(key)
        if result <> None:
            return int(result)
        return 0
    def delete(self,key):
        return self.connection.delete(key)
    def keys(self,key):
        return self.connection.keys(key)
    def clear(self):
        self.connection.flushdb()
