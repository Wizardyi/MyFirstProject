PROJECT(CACHE)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin ) 
SET(WORK_PATH ${PROJECT_BINARY_DIR}/../../../)
SET(ONLINE_PROTO_PATH ${WORK_PATH}proto/online/)
SET(CACHE_PROTO_PATH ${WORK_PATH}proto/cache/)
SET(SHARE_PROTO_PATH ${WORK_PATH}proto/share/)
SET(HIREDIS_LIBRARY_PATH ${PROJECT_BINARY_DIR}/../logic/redislib/)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(taomee REQUIRED)
find_package(taomee++ REQUIRED)
find_package(glib REQUIRED)
find_package(libxml2 REQUIRED)

set (DIR_SRCS
	)
AUX_SOURCE_DIRECTORY(./ 		DIR_SRCS)
AUX_SOURCE_DIRECTORY(./logic 	DIR_SRCS)

set (DATA_LIST
	global_data/global_data.cpp)

INCLUDE_DIRECTORIES("/usr/include/libxml2" ${GLIB_INCLUDE_DIR} ${WORK_PATH} "." "./logic" ${SHARE_PROTO_PATH})
ADD_LIBRARY(cache SHARED ${DIR_SRCS})
TARGET_LINK_LIBRARIES (cache "xml2" "taomee++" "taomee" "jsoncpp" "protobuf" "crypto" -L${ONLINE_PROTO_PATH} "onlineproto" -L${CACHE_PROTO_PATH} "cacheproto" -L${SHARE_PROTO_PATH} "shareproto" -L${HIREDIS_LIBRARY_PATH} "hiredis")
#ADD_DEFINITIONS( "-Wall -DCLIENT -DDEBUG -Werror -fPIC -ggdb -DUSE_TLOG -DENABLE_TRACE_LOG -std=c++11" )
ADD_DEFINITIONS( "-Wall -DDEBUG -Werror -fPIC -ggdb  -DENABLE_TRACE_LOG -std=c++11" )

INCLUDE_DIRECTORIES(${WORK_PATH})
ADD_LIBRARY(data SHARED ${DATA_LIST})
TARGET_LINK_LIBRARIES (data "xml2" "taomee++" "taomee" "crypto" )
ADD_DEFINITIONS( "-Wall -DDEBUG -Werror -fPIC -ggdb -D__USE_STRING_INLINES" )

