cmake_minimum_required(VERSION 2.6)
PROJECT(central)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)


SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)

ADD_DEFINITIONS(-ggdb -O0 -W -Wall -Wno-deprecated -Wno-unused-parameter -Wno-unused-variable -std=c++11 -fstack-protector-all)  

INCLUDE_DIRECTORIES(./ ../common ../proto)
LINK_DIRECTORIES(./ ../common ../proto)

ADD_EXECUTABLE(central ${SRC_LIST})

TARGET_LINK_LIBRARIES(central pthread stdc++ m boost_thread boost_system boost_date_time boost_regex common proto)
