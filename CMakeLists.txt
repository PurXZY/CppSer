cmake_minimum_required(VERSION 3.10)
project(test)

INCLUDE_DIRECTORIES("/usr/local/include")
LINK_DIRECTORIES("/usr/local/lib")

add_definitions("-Wall -std=c++11 -g -DDEBUG")

add_subdirectory(net lib)
aux_source_directory(. SRC_LIST)
add_executable(test ${SRC_LIST})
target_link_libraries(test event util net protobuf)
