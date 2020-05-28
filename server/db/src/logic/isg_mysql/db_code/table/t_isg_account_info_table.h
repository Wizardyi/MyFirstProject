#pragma once
extern "C" {
#include <libtaomee/project/types.h>
}

#include <dbser/mysql_iface.h>
#include "Ctable.h"      
#include "dbproto.db.pb.h"
#include <bitset>
#include <stdint.h>
#include "dbproto.struct.pb.h"



class CAccountInfoTable : public Ctable
{
   public:
      CAccountInfoTable(mysql_interface* db);

      //read
      int readTable(int32_t userid, google::protobuf::RepeatedPtrField<dbproto::AccountInfo>& roInfo, userid_t userId);

      

      //insert
      int insertTable(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId);

      //update
      int updateTable(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId);

      //delete
      int deleteTable(int32_t userid,userid_t userId);

      // increase or descrease value
      int updateAdd(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId);
};

extern CAccountInfoTable* g_accountInfoTable;

