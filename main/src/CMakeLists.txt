PROJECT(main)
SET(MYSQLCLIENT_LIBRARY_PATH "/usr/lib64/mysql") 

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

AUX_SOURCE_DIRECTORY(user   DIR_SRCS)
AUX_SOURCE_DIRECTORY(logic   DIR_SRCS)
AUX_SOURCE_DIRECTORY(socket   DIR_SRCS)
AUX_SOURCE_DIRECTORY(db   DIR_SRCS)

ADD_EXECUTABLE(main ${DIR_SRCS}/../)

TARGET_LINK_LIBRARIES (main "jsoncpp" "pthread-2.31" "curl" "rdkafka" -L${MYSQLCLIENT_LIBRARY_PATH} "mysqlclient")

INCLUDE_DIRECTORIES("./user" "./logic" "./socket" "/usr/include/mysql")

ADD_DEFINITIONS( "-Wall -Werror -fPIC -ggdb  -pthread  -funroll-loops  -std=c++11")
