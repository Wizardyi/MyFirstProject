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
 * ���ݿ��쳣
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
 * ��������ת���쳣
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
 * ���ݿ�����
 */
class RdbConnection {
public:
    /**
     * ������
     */
    virtual ~RdbConnection() {}

    /**
     * �������ݿ�
     * @param ip IP
     * @param port �˿�
     * @param user �û���
     * @param password ����
     * @param db ���ݿ���
     */
    virtual void connect(const std::string& ip, int32_t port, const std::string& user,
        const std::string& password, const std::string& db = "") throw(RdbException) = 0;

    /**
     * ִ��SQL
     * @param sql SQL���
     * @return ���
     */
    virtual RdbResult* execute(const std::string& sql) throw(RdbException) = 0;

    /**
     * ����������ת��
     * @param buffer ���������ݵ�ַ
     * @param size ���������ݳ���
     * @return ת��������
     */
    virtual const char* escape(const char* buffer, int32_t size) = 0;

    /**
     * ����������ת��
     * @param buffer �����������ַ���
     * @return ת��������
     */
    virtual const char* escape(const std::string& binary) = 0;

    /**
     * �������MySQL�Ƿ�����TIMEOUT
     */
    virtual void keepAlive() = 0;

};

/**
 * ���ݿ�ִ�н��
 */
class RdbResult {
public:
    /**
     * ������
     */
    virtual ~RdbResult() {}

    /**
     * �Ƿ�ɹ�
     * @retval true �ɹ�
     * @retval false ʧ��
     */
    virtual bool isSuccess() = 0;

    /**
     * �Ƿ��н����
     * @retval true ��
     * @retval false û��
     */
    virtual bool hasResultSet() = 0;

    /**
     * ȡ�ý����
     * @return �����
     */
    virtual RdbResultSet* getResultSet() = 0;

    /**
     * ȡ����Ӱ���������
     * @return ��Ӱ���������
     */
    virtual int getAffectedRow() = 0;

    /**
     * ��ȡ����ID
     * @return ����ID
     */
    virtual int getErrorId() = 0;

    /**
     * ��ȡ��������
     * @return ��������
     */
    virtual const std::string& getErrorString() = 0;
};

/**
 * �����
 */
class RdbResultSet {
public:
    /**
     * ������
     */
    virtual ~RdbResultSet() {}

    /**
     * ��������Ƿ��и���Ľ��
     * @retval true ��
     * @retval false û��
     */
    virtual bool hasNext() = 0;

    /**
     * ���������һ��
     * @return ��һ��
     */
    virtual RdbRow* next() = 0;

    /**
     * ȡ�ý������������
     * @return �������������
     */
    virtual int getRowCount() = 0;

    /**
     * ������Ƿ��Ѿ�����
     * @retval true ��
     * @retval false ��
     */
    virtual bool isOpened() = 0;

    /**
     * ȡ�ý����������
     * @return �����������
     */
    virtual int32_t getFieldNum() = 0;

    /**
     * ��ȡ��������
     * @return ��������,��0��β
     */
    virtual char** getFieldNames() = 0;
};

/**
 * �������һ��
 */
class RdbRow {
public:
    virtual ~RdbRow() {}

    /**
     * ��ȡBlob����
     * @param index ���ڵ�����
     * @param blob ���ص�Blob������
     * @param length Blob����
     */
    virtual void getBlob(int index, void* blob, int* length) = 0;

    /**
     * ��ȡ�ַ�������
     * @param index ���ڵ�����
     * @return �ַ���
     */
    virtual const char* getString(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡint����
     * @param index ���ڵ�����
     * @return ����
     */
    virtual int getInt(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡlong����
     * @param index ���ڵ�����
     * @return ����
     */
    virtual long getLong(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡunsigned int����
     * @param index ���ڵ�����
     * @return �޷�������
     */
    virtual unsigned int getUint(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡunsigned long long����
     * @param index ���ڵ�����
     * @return �޷�������
     */
    virtual unsigned long long getUllong(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡfloat����
     * @param index ���ڵ�����
     * @return �����ȸ�����
     */
    virtual float getFloat(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡdouble����
     * @param index ���ڵ�����
     * @return ˫���ȸ�����
     */
    virtual double getDouble(int index) throw(RdbInvalidConversionException) = 0;

    /**
     * ��ȡbool����
     * @param index ���ڵ�����
     * @return true��false
     */
    virtual bool getBool(int index) throw(RdbInvalidConversionException) = 0;
};

}

#endif // RDB_H
