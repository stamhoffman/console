cmake_minimum_required(VERSION 2.4)

project(consol_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(CLIENT_TARGET client)
set(SERVER_TARGET server)

set(CLIENT_SOURCES src/client/client.cpp)
set(SERVER_SOURCES src/server/server.cpp)

add_executable(${CLIENT_TARGET} ${CLIENT_SOURCES})
target_link_libraries(${CLIENT_TARGET} pthread)
add_executable(${SERVER_TARGET} ${SERVER_SOURCES})
target_link_libraries(${SERVER_TARGET} pthread)
