cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_library(net STATIC ${SRC_LIST})
