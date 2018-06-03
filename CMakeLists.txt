cmake_minimum_required(VERSION 2.4)

project(consol_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(CLIENT_TARGET client)
set(SERVER_TARGET server)
set(TEST_TARGET runtest)

set(CLIENT_SOURCES src/client/client.cpp)
set(SERVER_SOURCES src/server/server.cpp)
set(PARSLINE_SOURCES src/server/parse_line.h)

find_package(Threads REQUIRED)

add_executable(${CLIENT_TARGET} ${CLIENT_SOURCES})
target_link_libraries(${CLIENT_TARGET} ${CMAKE_THREAD_LIBS_INIT})
add_executable(${SERVER_TARGET} ${SERVER_SOURCES})
target_link_libraries(${SERVER_TARGET} ${CMAKE_THREAD_LIBS_INIT})

set(FILES_TO_FORMAT
  ${CMAKE_CURRENT_SOURCE_DIR}/${CLIENT_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/${SERVER_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/${PARSLINE_SOURCES}
  )

set(CLANG_FORMAT_ARGS -i -style=llvm)
include(clang-format.cmake)

set(FILES_TO_CHECK
  ${CMAKE_CURRENT_SOURCE_DIR}/${CLIENT_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/${SERVER_SOURCES}
  )
set(CPPCHEK_ARGS --enable=all --inconclusive --std=c++11)
include(cppcheck.cmake)

add_executable(${TEST_TARGET}
  src/test/test.cpp
  src/test/catch.hpp
  src/server/parse_line.h
  )
target_include_directories(${TEST_TARGET} PRIVATE src/server)
