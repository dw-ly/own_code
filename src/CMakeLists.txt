cmake_minimum_required(VERSION 3.16)
include_directories(${PROJECT_SOURCE_DIR}/libThreadPool)
include_directories(${PROJECT_SOURCE_DIR}/amqp/include)
link_directories(${PROJECT_SOURCE_DIR}/amqp/lib)

# add_subdirectory(net)

file(GLOB_RECURSE APP_SRC true *.cpp) #添加当前目录所有cpp文件到APP_SRC变量中
# set(APP_SRC main.cpp channelHandle.cpp connectionHandle.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(threadpool ${APP_SRC})
target_link_libraries(threadpool libThreadPool)
target_link_libraries(threadpool libamqpcpp.a)
