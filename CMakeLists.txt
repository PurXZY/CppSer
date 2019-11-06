cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("../libevent-master/build/include")
LINK_DIRECTORIES("/usr/local/lib")
LINK_DIRECTORIES("../libevent-master/build/lib/Release")
include_directories(../libevent-master/include)
include_directories(../libevent-master/build/include)
link_directories(../libevent-master/build/lib/Release)
add_definitions("-Wall -std=c++11 -g -DDEBUG")

add_subdirectory(net lib)

aux_source_directory(. SRC_LIST)
add_executable(test ${SRC_LIST})

target_link_libraries(test event net wsock32)
