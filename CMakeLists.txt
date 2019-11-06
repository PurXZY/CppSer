cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 14)

IF (WIN32)
    include_directories(../libevent-master/include)
    include_directories(../libevent-master/build/include)
    link_directories(../libevent-master/build/lib/Release)
else()
    INCLUDE_DIRECTORIES("/usr/local/include")
    LINK_DIRECTORIES("/usr/local/lib")
ENDIF()


add_definitions("-Wall -std=c++11 -g -DDEBUG")
add_subdirectory(net lib)
add_subdirectory(proto proto)

aux_source_directory(. SRC_LIST)
add_executable(test ${SRC_LIST})

IF (WIN32)
    target_link_libraries(test event net wsock32)
else()
    target_link_libraries(test event net)
ENDIF()
