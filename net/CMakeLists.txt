cmake_minimum_required(VERSION 3.0)
aux_source_directory(. net_src_list)
add_library(net STATIC ${net_src_list})
target_link_libraries(net event)
