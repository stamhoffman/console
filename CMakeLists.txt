cmake_minimum_required(VERSION 2.4)


project(consol_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(Target_1 client)
set(Target_2 server)

set(SOURCES_client src/client/client.cpp)
set(SOURCES_server src/server/server.cpp)

add_executable(${Target_1} ${SOURCES_client})
add_executable(${Target_2} ${SOURCES_server})
