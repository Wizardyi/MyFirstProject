PROJECT(main)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

AUX_SOURCE_DIRECTORY(user   DIR_SRCS)
AUX_SOURCE_DIRECTORY(logic   DIR_SRCS)
AUX_SOURCE_DIRECTORY(socket   DIR_SRCS)

ADD_EXECUTABLE(main ${DIR_SRCS}/../)

TARGET_LINK_LIBRARIES (main "jsoncpp" "pthread-2.17" "curl" "rdkafka")

INCLUDE_DIRECTORIES("./user" "./logic" "./socket")

ADD_DEFINITIONS( "-Wall -Werror -fPIC -ggdb  -pthread  -funroll-loops  -std=c++11")
