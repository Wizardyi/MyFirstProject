#!/usr/bin/python
#coding: utf-8

import MySQLdb as mdb
import re
import copy
import re
import os
import shutil
import string

con = mdb.connect('192.168.2.235', 'inksg', 'isg@mysql', 'ISG_ACCOUNT')
cur = con.cursor()


def saveFile(path, data):
    file = open(path, 'w')
    if file:
        file.write(data)
        file.close()

def readFile(path):
    f = open(path, 'r')

    content = ''
    if f:
        content = f.read()

    return content

class tableInfo:
    _select_cols = []
    _pri_cols = []
    _table_cols = []
    _pri_desc = ''
    def __init__(self, database_name, class_name, proto_info_name, base_class_name, global_var_name, key_col_name, is_repeated, is_auto_incre, select_cols, comment = ''):
        self._class_name = class_name     # 类名
        self._proto_info_name = proto_info_name     # proto中message名
        self._base_class_name = base_class_name
        self._global_var_name = global_var_name
        self._database_name = database_name
        self._is_repeated = is_repeated
        self._is_auto_incre = is_auto_incre
        self._key_col_name = key_col_name
        self._select_cols = select_cols
        self._comment = comment
        self._processor_class_name_prefix = "CS" + self._proto_info_name
        self._processor_class_name_suffix = "Processor"
        self._proto_data_class_name = "dbproto::CS%sData" % (self._proto_info_name)

    def setTablePriCols(self, pri_col):
        self._pri_cols = copy.deepcopy(pri_col)

    def setTableCols(self, cols):
        self._table_cols = copy.deepcopy(cols)

        
    def setPriDesc(self, pri_desc):
        self._pri_desc = pri_desc

class colInfo:
    def __init__(self, col_name, proto_type, cpp_type, is_pri, db_col_type):
        self._col_name = col_name     # 列名
        self._proto_type = proto_type
        self._cpp_type = cpp_type
        self._is_pri = is_pri
        self._db_col_type = db_col_type

        
class typeInfo:
    def __init__(self, cpp_type, proto_type):
        self._cpp_type = cpp_type
        self._proto_type = proto_type     

def getColByName(table, colName):
    if table:
        for col in table._table_cols:
            if colName == col._col_name:
                return col

    return None

def getTableColByName(tableName, colName):
    return getColByName(table_to_class_name_map.get(tableName), colName)

def getTableClassName(tableName):
   return table_to_class_name_map[tableName]._class_name

def getTableProtoInfoName(tableName):
   return table_to_class_name_map[tableName]._proto_info_name

def getTableReadType(tableName):
   str = ''
   is_repeated = table_to_class_name_map[tableName]._is_repeated
   if is_repeated:
      str = 'google::protobuf::RepeatedPtrField<dbproto::' + getTableProtoInfoName(tableName) + '>'
   else:   
      str = 'dbproto::' + getTableProtoInfoName(tableName)
   return str

def getReadColsParamsStr(table):
    params = []

    for colName in table._select_cols:
        col = getColByName(table, colName)

        if col:
            params.append(col._cpp_type + ' _' + col._col_name)

    return params

def getReadColsParamlistStr(table):
    params = getReadColsParamsStr(table)

    if len(params) > 0:
        return ', '.join(params) + ', ';
    else:
        return '';

def getTableReadColsDeclare(tableName):
    str = ''
    info = table_to_class_name_map[tableName]

    if info and len(info._table_cols) > 0 and len(info._select_cols) > 0:
        str = 'int readTableByCols(%(params_str)s%(table_read_type)s& roInfo, userid_t userId);' % {
                'params_str': getReadColsParamlistStr(info),
                'table_read_type': getTableReadType(tableName)}

    return str

def getReadColsSqlConditionlistStr(table):
    conditions = []

    for colName in table._select_cols:
        col = getColByName(table, colName)

        if col: conditions.append(' << "`%(name)s` = " << _%(name)s' % { 'name': col._col_name })

    conditionlist_str = ''

    if len(conditions) > 0:
        conditionlist_str += ' << " WHERE "' + ' << " and "'.join(conditions)

    return conditionlist_str

def getTableReadColsDefine(tableName):
    str = ''
    info = table_to_class_name_map[tableName]

    if info and len(info._table_cols) > 0 and len(info._select_cols) > 0:
        str = '''int %(table_class_name)s::readTableByCols(%(params_str)s%(table_read_type)s& roInfo, userid_t userId){
    std::stringstream oss;
    oss << "SELECT %(select_sql_param)s FROM " << %(table_op_table_name)s%(conditions_str)s;

    GEN_SQLSTR(this->sqlstr, oss.str().c_str());
    MYSQL_RES* res = NULL;
    MYSQL_ROW  row;
    int ret = this->db->exec_query_sql(sqlstr, &res);
    if (ret) {
       ERROR_LOG("exec sql failed: %%s", this->sqlstr);
       return ret; 
    }
    while ((row = mysql_fetch_row(res)) != NULL) {
        dbproto::%(table_proto_name)s* info = roInfo.Add();
%(table_read_assign)s
    }
    
    mysql_free_result(res);
    return 0;
}''' % {'table_class_name': getTableClassName(tableName),
        'table_read_type': getTableReadType(tableName),
        'table_read_assign': getTableReadAssign(info._table_cols),
        'select_sql_param': getSelectSqlParam(info._table_cols),
        'table_op_table_name': getTableOpTableName(tableName),
        'table_proto_name': getTableProtoInfoName(tableName),
        'params_str': getReadColsParamlistStr(info),
        'conditions_str': getReadColsSqlConditionlistStr(info)}

    return str

def getTableBaseCalssName(tableName):
   return table_to_class_name_map[tableName]._base_class_name

def getTableGlobalVarName(tableName):
   return table_to_class_name_map[tableName]._global_var_name

def getDeleteTablePriDesc(tableName):
   return table_to_class_name_map[tableName]._pri_desc

def getDeleteTableSuffixUserIdParam(tableName):
    return (table_to_class_name_map[tableName]._pri_desc != '' and ',' or '') + 'userid_t userId';

def getTableKeyColName(tableName):
   return table_to_class_name_map[tableName]._key_col_name

def getTablePriDesc(tableName):
   desc = table_to_class_name_map[tableName]._pri_desc
   if len(desc) != 0:
       desc += ','
   return desc

def getTableDatabaseName(tableName):
   return table_to_class_name_map[tableName]._database_name

def getTableIsRepeated(tableName):
   return table_to_class_name_map[tableName]._is_repeated

def getTableIsGlobal(tableName):
   #return table_to_class_name_map[tableName]._is_global
    return table_to_class_name_map[tableName]._base_class_name == 'Ctable'

def getTablePriCols(tableName):
   return table_to_class_name_map[tableName]._pri_cols

def parseTable(raw_table_name, table_name):
   global cur
   t = table_to_class_name_map[raw_table_name]
   sql = "DESC " + table_name
   col_list = []
   pri_cols = []
   cur.execute(sql)
   rows = cur.fetchall()
   desc = ''
   enum_desc = ''
   pri_desc = ''
   index = 1
   size = len(rows)
   key_num = 0
   for row in rows:
      row_name = row[0]
      row_type = row[1]
      pri_key = row[3]
      
      for (key, val) in type_to_name_map.items():
         pattern = re.compile(key)
         result = pattern.match(row_type)
         if result:
            is_pri = False
            #生成主键类型
            if pri_key == 'PRI':
               pri_cols.append(colInfo(row_name, val._proto_type, val._cpp_type, is_pri, row_type))
               is_pri = True
               if key_num > 0:
                  pri_desc += ', '
               pri_desc += val._cpp_type + ' ' + row_name
               key_num += 1

            col_list.append(colInfo(row_name, val._proto_type, val._cpp_type, is_pri, row_type))

            #生成proto枚举定义
            enum_desc = '\tEnum_' + row_name

            #生成proto类型定义
            desc += '\t'+ val._proto_type + ' ' + row_name + ' = ' + str(index) + ';'
            if index != size:
                desc += '\n'
            index += 1
            break;
   t.setPriDesc(pri_desc)
   t.setTableCols(col_list)
   t.setTablePriCols(pri_cols)
   #print len(t._pri_cols), raw_table_name, len(t._table_cols)

#生成proto和代码文件
def genFile():
    proto_desc = ''
    global cur
    curDb = 'ISG_ACCOUNT'
    for (table_name, table) in table_to_class_name_map.items():
        raw_table_name = table_name
        dbName = table._database_name
        if table._base_class_name == 'CtableRoute100x10':
            table_name += '_0'
            dbName += '_00'
        elif table._base_class_name == 'CtableRoute':
            table_name += '_00'
            dbName += '_00'
        if table._database_name != curDb:
            con = mdb.connect('192.168.2.235', 'inksg', 'isg@mysql', dbName)
            cur = con.cursor()
            curDb = table._database_name

        parseTable(raw_table_name, table_name)
        genTableHeaderFile(raw_table_name)
        genTableCppFile(raw_table_name)
        proto_desc += genProtoDesc(raw_table_name)
    str = proto_declare%({'proto_desc':proto_desc})
    saveFile('./dbproto.struct.proto', str)

#产生单个表的proto相关
def genProtoDesc(tableName):
   t = table_to_class_name_map[tableName]
   cols = t._table_cols[:]
   enum_desc = ''
   info_desc = ''
   index = 1
   size = len(cols)
   for col in cols:
      enum_desc += '\tEnum_' + tableName + '_' + col._col_name + ' = ' + str(index - 1) + ';'
      info_desc  += '\t'+ col._proto_type + ' ' + col._col_name + ' = ' + str(index) + ';'
      if index != size:
         info_desc += '\n'
         enum_desc += '\n' 
      index += 1
   enum_desc += '\n\tEnum_'+ tableName +'_Max = ' + str(index-1) + ';'      
   desc = proto_desc%({'table_proto_name':getTableProtoInfoName(tableName),'proto_enum_desc':enum_desc, 'proto_info_desc':info_desc})
   return desc

def genTableHeaderFile(tableName):
   str = header_declare%({'table_class_name':getTableClassName(tableName), \
                          'table_read_type':getTableReadType(tableName),   \
                          'table_proto_name':getTableProtoInfoName(tableName), \
                          'base_class_name':getTableBaseCalssName(tableName), \
                          'pri_desc':getTablePriDesc(tableName), \
                          'del_pri_desc':getDeleteTablePriDesc(tableName), \
                          'del_suffix_userid_param':getDeleteTableSuffixUserIdParam(tableName), \
                          'in_out_param':getTableInsertInOutParam(tableName), \
                          'table_read_cols_declare':getTableReadColsDeclare(tableName), \
                          'global_var_name':getTableGlobalVarName(tableName)}) 
   saveFile('db_code/table/'+tableName+'_table.h', str)

def genTableCppFile(tableName):
   t = table_to_class_name_map[tableName]
   cols = t._table_cols[:]
   str = cpp_compl%({'table_class_name':getTableClassName(tableName), \
                     'table_read_type':getTableReadType(tableName),   \
                     'key_name':getTableKeyName(tableName),     \
                     'table_read_cols_define':getTableReadColsDefine(tableName), \
                     'table_op_table_name':getTableOpTableName(tableName),  \
                     'table_read_condition':getTableReadDelCondition(tableName, True),   \
                     'table_update_condition':getTableInsertUpdateCondition(tableName, False),   \
                     'table_del_condition':getTableReadDelCondition(tableName, False),   \
                     'table_insert_condition':getTableInsertUpdateCondition(tableName, True),   \
                     'table_proto_name':getTableProtoInfoName(tableName), \
                     'base_class_name':getTableBaseCalssName(tableName), \
                     'pri_desc':getTablePriDesc(tableName), \
                     'global_var_name':getTableGlobalVarName(tableName),\
                     'table_name':tableName,\
                     'table_read_assign':getTableReadAssign(cols), \
                     'in_out_param':getTableInsertInOutParam(tableName), \
                     'insert_sql_statement':getTableInsertSqlStatement(tableName), \
                     'select_sql_param':getSelectSqlParam(cols),  \
                     'del_pri_desc':getDeleteTablePriDesc(tableName), \
                     'del_suffix_userid_param':getDeleteTableSuffixUserIdParam(tableName), \
                     'table_update_desc':getTableUpdateDesc(tableName,getTableProtoInfoName(tableName), cols), \
                     'table_add_desc':getTableAddDesc(tableName,getTableProtoInfoName(tableName), cols), \
                     'table_insert_desc':getTableInsertDesc(tableName,getTableProtoInfoName(tableName), cols), \
                     'db_name':getTableDatabaseName(tableName)})
   saveFile('db_code/table/'+tableName+'_table.cpp', str)

def getSelectSqlParam(cols):
    str = ''
    index = 0
    size = len(cols)
    for col in cols:
        if index > 0:
            str += ','
        if col._db_col_type == 'datetime':
            str += 'UNIX_TIMESTAMP(`' + col._col_name + '`)'
        else:
            str += '`'+ col._col_name + '`'
        index += 1
    return str
        

def getTableInsertInOutParam(tableName):
    t = table_to_class_name_map[tableName]
    if t._is_auto_incre:
        pri_cols = getTablePriCols(tableName)
        return ', ' + pri_cols[0]._cpp_type + '& ro' + pri_cols[0]._col_name
    else:
        return ''

def getTableInsertSqlStatement(tableName):
     t = table_to_class_name_map[tableName]
     if t._is_auto_incre:
        pri_cols = getTablePriCols(tableName)
        return '''
uint32_t _rid = 0;
int ret = this->exec_insert_sql_get_auto_increment_id(this->sqlstr, KEY_EXISTED_ERR, &_rid);
ro%s = _rid; 
''' % (pri_cols[0]._col_name)
     else:
        return 'int ret = this->exec_insert_sql(this->sqlstr, KEY_EXISTED_ERR);'
    

def getTableReadAssign(cols):
    assign_desc = ''
    index = 0
    size = len(cols)
    
    for col in cols:
        if col._proto_type == 'string' or col._proto_type == 'bytes':
            assign_desc +='\tinfo->set_' + col._col_name + '(row[' + str(index) + ']);'
        else:
            assign_desc += '\tinfo->set_' + col._col_name + '(atoi_safe(row[' + str(index) + ']));'
        if index+1 != size:
            assign_desc += '\n'
        index += 1
    return assign_desc    

def getTableReadDelCondition(tableName, isRead):
   is_global = getTableIsGlobal(tableName)
   if is_global and isRead:
      return ';'
   index = 1
   pri_cols = getTablePriCols(tableName)
   size = len(pri_cols)
   if size == 0:
       return ';'
   str = '<< " WHERE '
   
   
   for col in pri_cols:
      str += '`' + col._col_name + '` = " << ' + col._col_name
      if index < size:
         str += ' << " AND '
         index += 1
   #print size, tableName,str
   return str + ';'
   
def getTableInsertUpdateCondition(tableName, isInsert):
   if isInsert:
       return ';'
   
   index = 1
   pri_cols = getTablePriCols(tableName)
   size = len(pri_cols)
   #print size, tableName 
   if size == 0:
       return ';'
   str = '<< " WHERE '
   
   for col in pri_cols:
      str += '`' + col._col_name + '` = " << roInfo.' + col._col_name + '()'
      if index < size:
         str += ' << " AND '
         index += 1
   #print size, tableName,str
   return str + ';'

def getTableKeyName(tableName):
    base_class_name = getTableBaseCalssName(tableName)
    if base_class_name == 'Ctable':
        return ''
    else:
        return ', "'+ getTableKeyColName(tableName) +'"'

def getTableOpTableName(tableName):
   base_class_name = getTableBaseCalssName(tableName)
   if base_class_name == 'Ctable':
      return 'this->get_table_name()'
   else:
       pri_cols = getTablePriCols(tableName)
       return 'this->get_table_name(userId)'

def getTableUpdateDesc(table_name, table_proto_name, cols):
    update_desc = ''
    index = 0
    size = len(cols)

    for col in cols:
        desc = '''\t\tcase dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_%(col_name)s:
\t\t{
\t\t    if(!ossVal.str().empty()){
\t\t        ossVal << ",";
\t\t    }
\t\t    ossVal << "`%(col_name)s` = " << %(col_val)s;
\t\t}
\t\tbreak;'''
        if col._proto_type == 'string' or col._proto_type == 'bytes':
            update_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':'"\'" << roInfo.' + col._col_name + '() << "\'"'})
        else :
            if col._db_col_type == 'datetime':                
                update_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':' "FROM_UNIXTIME(" << roInfo.' + col._col_name + '() << ")"'})
                #  print '===============' + update_desc
            else:
                update_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':'roInfo.'+col._col_name+'()'})
        index += 1
        if index != size:
            update_desc += '\n'
    return update_desc

def getTableAddDesc(table_name, table_proto_name, cols):
    update_desc = ''
    ignore_cols = []

    for col in cols:
        if not re.match('^(int|integer|smallint|bigint|tinyint|mediumint|decimal|numeric|float|double)', col._db_col_type):
            ignore_cols.append(col)
            continue

        desc = '''\t\tcase dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_%(col_name)s:
\t\t{
\t\t    if(!ossVal.str().empty()){
\t\t        ossVal << ",";
\t\t    }
\t\t    ossVal << "`%(col_name)s` = `%(col_name)s` + " << %(col_val)s;
\t\t}
\t\tbreak;'''
        update_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':'roInfo.'+col._col_name+'()'})
        update_desc += '\n'

    if len(ignore_cols) > 0:
        for col in ignore_cols:
            update_desc += "\t\tcase dbproto::Enum%s::Enum_%s_%s:\n" % (table_proto_name, table_name, col._col_name);
        update_desc += "\t\t\tERROR_LOG(\"can't add non numberic column %s value in table %s\");\n" % (col._col_name, table_name)
        update_desc += "\t\t\tbreak;\n";

    return update_desc

def getTableInsertDesc(table_name, table_proto_name, cols): 
    insert_desc = ''
    index = 0
    size = len(cols)
    
    for col in cols:
        desc = '''\t\tcase dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_%(col_name)s:
\t\t{
\t\t    if(!ossName.str().empty()){
\t\t        ossName << ",";
\t\t        ossVal << ",";
\t\t    }
\t\t    ossName << "`%(col_name)s`";
\t\t    ossVal << %(col_val)s;
\t\t}
\t\tbreak;'''
        if col._proto_type == 'string' or col._proto_type == 'bytes':
            insert_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':'"\'" << roInfo.' + col._col_name + '() << "\'"'})
        else :
            if col._db_col_type == 'datetime':
                insert_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':' "FROM_UNIXTIME(" << roInfo.' + col._col_name + '() << ")"'})
            else:    
                insert_desc += desc%({'table_name':table_name,'table_proto_name':table_proto_name,'col_name':col._col_name,'col_val':'roInfo.' + col._col_name + '()'})
        index += 1
        if index != size:
            insert_desc += '\n'
    return insert_desc
    

#数据库类型对应生成代码的信息
type_to_name_map = {
   'bigint*':typeInfo('int64_t', 'int64'),
   'int*':typeInfo('int32_t', 'int32'),
   'tinyint*':typeInfo('int32_t', 'int32'),
   'varchar*':typeInfo('std::string', 'string'),
   'datetime':typeInfo('uint32_t', 'uint32'),
   'smallint*':typeInfo('int32_t', 'int32'),
   'text':typeInfo('std::string', 'bytes'),
   'float':typeInfo('float', 'float')
   }



#数据库表名对应生成代码的信息
table_to_class_name_map = {
    't_isg_account_info':tableInfo('ISG_ACCOUNT','CAccountInfoTable', 'AccountInfo', 'Ctable', 'g_accountInfoTable', '', True, False,[], '玩家信息'),
}

proto_declare = '''syntax="proto3";
package dbproto;

%(proto_desc)s

'''

proto_desc = '''
//########################################

enum Enum%(table_proto_name)s{
   %(proto_enum_desc)s
}

message %(table_proto_name)s{
   %(proto_info_desc)s
}

'''


header_declare = '''#pragma once
extern "C" {
#include <libtaomee/project/types.h>
}

#include <dbser/mysql_iface.h>
#include "%(base_class_name)s.h"      
#include "dbproto.db.pb.h"
#include <bitset>
#include <stdint.h>
#include "dbproto.struct.pb.h"



class %(table_class_name)s : public %(base_class_name)s
{
   public:
      %(table_class_name)s(mysql_interface* db);

      //read
      int readTable(%(pri_desc)s %(table_read_type)s& roInfo, userid_t userId);

      %(table_read_cols_declare)s

      //insert
      int insertTable(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo%(in_out_param)s, userid_t userId);

      //update
      int updateTable(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo, userid_t userId);

      //delete
      int deleteTable(%(del_pri_desc)s%(del_suffix_userid_param)s);

      // increase or descrease value
      int updateAdd(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo, userid_t userId);
};

extern %(table_class_name)s* %(global_var_name)s;

'''

cpp_compl = '''#include "%(table_name)s_table.h"
#include "share/err.h"
#include "utils.h"

%(table_class_name)s::%(table_class_name)s(mysql_interface* db)
      : %(base_class_name)s(db, "%(db_name)s", "%(table_name)s"%(key_name)s){      
}

int %(table_class_name)s::readTable(%(pri_desc)s %(table_read_type)s& roInfo, userid_t userId){
    std::stringstream oss;
    oss << "SELECT %(select_sql_param)s FROM " << %(table_op_table_name)s %(table_read_condition)s

    GEN_SQLSTR(this->sqlstr, oss.str().c_str());
    MYSQL_RES* res = NULL;
    MYSQL_ROW  row;
    int ret = this->db->exec_query_sql(sqlstr, &res);
    if (ret) {
       ERROR_LOG("exec sql failed: %%s", this->sqlstr);
       return ret; 
    }
    while ((row = mysql_fetch_row(res)) != NULL) {
        dbproto::%(table_proto_name)s* info = roInfo.Add();
%(table_read_assign)s
    }
    
    mysql_free_result(res);
    return 0;
}

%(table_read_cols_define)s

int %(table_class_name)s::insertTable(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo%(in_out_param)s, userid_t userId){
    std::stringstream oss;
    oss << "INSERT INTO " << %(table_op_table_name)s;
    std::bitset<64> oBit(bitSet);
    std::stringstream ossName;
    std::stringstream ossVal;
    for(int32_t i = 0; i < dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
%(table_insert_desc)s
            }
        }
    }
    oss << "(" << ossName.str() << ") values(" << ossVal.str() << ");";
    GEN_SQLSTR(this->sqlstr, oss.str().c_str());

    %(insert_sql_statement)s;
    if (ret != DB_SUCC) 
    {
        ERROR_LOG("exec sql failed: %%s", this->sqlstr);
    }
    return ret; 
}

int %(table_class_name)s::updateTable(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo, userid_t userId){
  std::stringstream oss,ossVal;
  std::bitset<64> oBit(bitSet);
  for(int32_t i = 0; i < dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
%(table_update_desc)s
            }
        }
    }
  oss << "UPDATE " << %(table_op_table_name)s << " SET " << ossVal.str() %(table_update_condition)s
  GEN_SQLSTR(this->sqlstr, oss.str().c_str());
  return this->exec_update_sql(this->sqlstr,USER_ID_NOFIND_ERR );
}

int %(table_class_name)s::updateAdd(%(pri_desc)s uint64_t bitSet, dbproto::%(table_proto_name)s& roInfo, userid_t userId){
  std::stringstream oss,ossVal;
  std::bitset<64> oBit(bitSet);
  for(int32_t i = 0; i < dbproto::Enum%(table_proto_name)s::Enum_%(table_name)s_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
%(table_add_desc)s
            }
        }
    }
  oss << "UPDATE " << %(table_op_table_name)s << " SET " << ossVal.str() %(table_update_condition)s
  GEN_SQLSTR(this->sqlstr, oss.str().c_str());
  return this->exec_update_sql(this->sqlstr,USER_ID_NOFIND_ERR );
}

int %(table_class_name)s::deleteTable(%(del_pri_desc)s%(del_suffix_userid_param)s){
    std::stringstream oss;
    oss << "DELETE FROM " << %(table_op_table_name)s %(table_del_condition)s
    GEN_SQLSTR(this->sqlstr, oss.str().c_str());
    int ret = this->exec_delete_sql(this->sqlstr, USER_ID_NOFIND_ERR);
    if (ret != DB_SUCC) 
    {
        ERROR_LOG("exec sql failed: %%s", this->sqlstr);
    }
    return ret; 
}

'''

def prepare():
    if os.path.exists("db_code"):
        shutil.rmtree("db_code")

    os.makedirs("db_code/table")

table_operations_name = ('Insert', 'Delete', 'Update', 'Select', 'UpdateAdd')

def genMsgProcessorCode():
    declares = ''
    declare_template = string.Template(readFile('./gen_msg_processor.declare.db.template'))
    
    defines = ''
    define_operations_template = (
            string.Template(readFile('./gen_msg_processor.define_insert.db.template')), string.Template(readFile('./gen_msg_processor.define_delete.db.template')),
            string.Template(readFile('./gen_msg_processor.define_update.db.template')),
            string.Template(readFile('./gen_msg_processor.define_select.db.template')),
            string.Template(readFile('./gen_msg_processor.define_update_add.db.template'))
            )

    define_insert_func_call_template = string.Template(
            readFile('./gen_msg_processor.define_insert_func_call.db.template'));

    define_insert_func_call_inc_template = string.Template(
            readFile('./gen_msg_processor.define_insert_func_call_inc.db.template'));

    includes = ''

    for table_name, table_info in table_to_class_name_map.iteritems():
        includes += "\n#include <table/" + table_name + "_table.h>";

        for op_idx in range(0, len(table_operations_name)):
            op_name = table_operations_name[op_idx]
            op_template = define_operations_template[op_idx]

            args = ', '.join(["table." + col._col_name + "()" for col in table_info._pri_cols])

            if len(table_info._pri_cols) > 0 and op_name.lower() != 'delete':
                args += ", "

            props = {
                    'table_processor_class_name': (table_info._processor_class_name_prefix + op_name +
                        table_info._processor_class_name_suffix),
                    'table_proto_data_name': table_info._proto_data_class_name,
                    'table_var_name': table_info._global_var_name,
                    'table_key_col_args': args,
                    'table_suffix_userid_param': (args != '' and ',' or '') + 'userid'
                    }

            if op_name.lower() == 'insert':
                func_call = ''
                if table_info._is_auto_incre:
                    props['table_return_id_type'] = table_info._pri_cols[0]._cpp_type
                    func_call = define_insert_func_call_inc_template.substitute(props)
                else:
                    func_call = define_insert_func_call_template.substitute(props)

                props['table_insert_func_call'] = func_call

            defines += "\n" + op_template.substitute(props)
            declares += "\n" + declare_template.substitute(props)

    saveFile('./db_code/gen_msg_processor.h', string.Template(readFile('./gen_msg_processor.h.db.template'))
            .substitute(table_processors_declare = declares))

    saveFile('./db_code/gen_msg_processor.cpp', string.Template(readFile('./gen_msg_processor.cpp.db.template'))
            .substitute(table_processors_include = includes, table_processors_define = defines))

prepare()
genFile()
genMsgProcessorCode()
