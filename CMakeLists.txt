cmake_minimum_required(VERSION 3.3)
project(lgtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
option(DEBUG "print information for debug." OFF)
configure_file(${CMAKE_BINARY_DIR}/../config.h.in ${CMAKE_BINARY_DIR}/../inc/config.h @ONLY)

add_library(LgTerm src/light-terminal.cpp)
include_directories(inc)
add_executable(lgtest test/test.cpp)
target_link_libraries(lgtest LgTerm curses)

