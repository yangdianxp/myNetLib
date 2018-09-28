cmake_minimum_required(VERSION 2.6)
PROJECT(net_base)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)


SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

SET(LIBRARY_OUTPUT_PATH ./)

ADD_DEFINITIONS(-ggdb -O0 -W -Wall -Wno-deprecated -Wno-unused-parameter -Wno-unused-variable -std=c++11 -fstack-protector-all -DBOOST_LOG_DYN_LINK)  

INCLUDE_DIRECTORIES(./ ../proto ../common)

ADD_LIBRARY(net_base STATIC ${SRC_LIST})

TARGET_LINK_LIBRARIES(net_base)
