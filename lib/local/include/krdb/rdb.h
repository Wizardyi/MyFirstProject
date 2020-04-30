#ifndef RDB_H
#define RDB_H

#include <cstdint>
#include <stdexcept>

namespace krdb {

class RdbConnection;
class RdbResult;
class RdbResultSet;
class RdbRow;

/**
 * 数据库异常
 */
class RdbException : public std::logic_error {
public:
    explicit RdbException(const std::string& reason)
    : logic_error(reason.c_str()) { // construct from message string
    }

	explicit RdbException(const char* reason)
    : logic_error(reason) {	// construct from message string
    }
};

/**
 * 数据类型转换异常
 */
class RdbInvalidConversionException : public std::logic_error {
public:
    explicit RdbInvalidConversionException(const std::string& reason)
    : logic_error(reason.c_str()) { // construct from message string
    }

	explicit RdbInvalidConversionException(const char* reason)
    : logic_error(reason) {	// construct from message string
    }
};

/**
 * 数据库连接
 */
class RdbConnection {
public:
    /**
     * 虚析构
     */
    virtual ~RdbConnection() {}

    /**
     * 连接数据库
     * @param ip IP
     * @param port 端口
     * @param user 用户名
     * @param password 密码
     * @param db 数据库名
     */
    virtual void connect(const std::string& ip, int32_t port, const std::string& user,
        const std::string& password, const std::string& db = "") throw(RdbException) = 0;

    /**
     * 执行SQL
     * @param sql SQL语句
     * @return 结果
     */
    virtual RdbResult* execute(const std::string& sql) throw(RdbException) = 0;

    /**
     * 二进制数据转义
     * @param buffer 二进制数据地址
     * @param size 二进制数据长度
     * @return 转义后的数据
     */
    virtual const char* escape(const char* buffer, int32_t size) = 0;

    /**
     * 二进制数据转义
     * @param buffer 二进制数据字符串
     * @return 转义后的数据
     */
    virtual const char* escape(const std::string& binary) = 0;

    /**
     * 保活，无论MySQL是否设置TIMEOUT
     */
    virtual void keepAlive() = 0;

};

/**
 * 数据库执行结果
 */
class RdbResult {
public:
    /**
     * 虚析构
     */
    virtual ~RdbResult() {}

    /**
     * 是否成功
     * @retval true 成功
     * @retval false 失败
     */
    virtual bool isSuccess() = 0;

    /**
     * 是否有结果集
     * @retval true 有
     * @retval false 没有
     */
    virtual bool hasResultSet() = 0;

    /**
     * 取得结果集
     * @return 结果集
     */
    virtual RdbResultSet* getResultSet() = 0;

    /**
     * 取得受影响的行数量
     * @return 受影响的行数量
     */
    virtual int getAffectedRow() = 0;

    /**
     * 获取错误ID
     * @return 错误ID
     */
    virtual int getErrorId() = 0;

    /**
     * 获取错误描述
     * @return 错误描述
     */
    virtual const std::string& getErrorString() = 0;
};

/**
 * 结果集
 */
class RdbResultSet {
public:
    /**
     * 虚析构
     */
    virtual ~RdbResultSet() {}

    /**
     * 结果集内是否有更多的结果
     * @retval true 有
     * @retval false 没有
     */
    virtual bool hasNext() = 0;

    /**
     * 结果集内下一行
     * @return 下一行
     */
    virtual RdbRow* next() = 0;

    /**
     * 取得结果集内行数量
     * @return 结果集内行数量
     */
    virtual int getRowCount() = 0;

    /**
     * 结果集是否已经开启
     * @retval true 是
     * @retval false 否
     */
    virtual bool isOpened() = 0;

    /**
     * 取得结果集列数量
     * @return 结果集列数量
     */
    virtual int32_t getFieldNum() = 0;

    /**
     * 获取列名数组
     * @return 列名数组,以0结尾
     */
    virtual char** getFieldNames() = 0;
};

/**
 * 结果集内一行
 */
class RdbRow {
public:
    virtual ~RdbRow() {}

    /**
     * 获取Blob类型
     * @param index 行内的索引
     * @param blob 返回的Blob缓冲区
     * @param length Blob长度
     */
    virtual void getBlob(int index, void* blob, int* length) = 0;

    /**
     * 获取字符串类型
     * @param index 行内的索引
     * @return 字符串
     */
    virtual const char* getString(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取int类型
     * @param index 行内的索引
     * @return 整数
     */
    virtual int getInt(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取long类型
     * @param index 行内的索引
     * @return 整数
     */
    virtual long getLong(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取unsigned int类型
     * @param index 行内的索引
     * @return 无符号整数
     */
    virtual unsigned int getUint(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取unsigned long long类型
     * @param index 行内的索引
     * @return 无符号整数
     */
    virtual unsigned long long getUllong(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取float类型
     * @param index 行内的索引
     * @return 单精度浮点数
     */
    virtual float getFloat(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取double类型
     * @param index 行内的索引
     * @return 双精度浮点数
     */
    virtual double getDouble(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * 获取bool类型
     * @param index 行内的索引
     * @return true或false
     */
    virtual bool getBool(int index) throw(RdbInvalidConversionException) = 0;
};

}

#endif // RDB_H
