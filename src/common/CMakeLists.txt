cmake_minimum_required(VERSION 2.6)
PROJECT(common)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)


SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

SET(LIBRARY_OUTPUT_PATH ./)

ADD_DEFINITIONS(-ggdb -O3 -W -Wall -Wno-deprecated -Wno-unused-parameter -Wno-unused-variable -std=c++11 -fstack-protector-all -DBOOST_LOG_DYN_LINK)  

INCLUDE_DIRECTORIES(./ ../proto)

ADD_LIBRARY(common STATIC ${SRC_LIST})

TARGET_LINK_LIBRARIES(common)
