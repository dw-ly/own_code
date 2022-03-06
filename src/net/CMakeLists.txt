cmake_minimum_required(VERSION 3.16)

set(LIB_NET tpcClient.cpp)
add_library(libtcp ${LIB_NET}) #.a
#add_library(libhello SHARED ${LIB_SRC}) #.so
#设置输出位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set_target_properties(libtcp PROPERTIES OUTPUT_NAME "tcp")