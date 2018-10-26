cmake_minimum_required(VERSION 2.6)
PROJECT(test)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)


SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

#set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")
#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)

ADD_DEFINITIONS(-g -ggdb -O0 -W -posix -Wall -Wno-deprecated -Wno-unused-parameter -Wno-unused-variable -std=c++11 -fstack-protector-all -DBOOST_LOG_DYN_LINK)  

INCLUDE_DIRECTORIES(./)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(test ${SRC_LIST})

TARGET_LINK_LIBRARIES(test stdc++ m pthread boost_log_setup boost_log boost_system boost_date_time boost_regex boost_filesystem boost_thread)
