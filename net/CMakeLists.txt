cmake_minimum_required(VERSION 3.0)
aux_source_directory(. SRC_LIST)
add_library(net STATIC ${SRC_LIST})
target_link_libraries(net event)
