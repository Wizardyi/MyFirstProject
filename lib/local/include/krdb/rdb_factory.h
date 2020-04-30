#ifndef RDB_FACTORY_H
#define RDB_FACTORY_H

#include "rdb.h"

namespace krdb {

class RdbFactory {
public:
    static krdb::RdbConnection* createConnection();
    static void destroyConnection(krdb::RdbConnection* connection);

private:
    RdbFactory();
    RdbFactory(const RdbFactory&);
};

}

#endif // RDB_FACTORY_H
