cmake_minimum_required(VERSION 3.16)
include_directories(${PROJECT_SOURCE_DIR}/libThreadPool)
include_directories(${PROJECT_SOURCE_DIR}/amqp/include)
link_directories(${PROJECT_SOURCE_DIR}/amqp/lib)
set(APP_SRC main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(threadpool ${APP_SRC})
target_link_libraries(threadpool libThreadPool)
target_link_libraries(threadpool libamqpcpp.a)
