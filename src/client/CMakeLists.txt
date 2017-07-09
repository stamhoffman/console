cmake_minimum_required (VERSION 2.6)

set (PROJECT client)
set (SRC_DIR ~/src/client)
set (BIN_DIR ~/bin)

add_definitions(-Wall -O2)/

add_executable (${PROJECT} ${BIN_DIR} ${SRC_DIR})
