cmake_minimum_required(VERSION 3.3)
project(lgtest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_library(LgTerm src/light-terminal.cpp)
include_directories(inc)
add_executable(lgtest test/test.cpp)
target_link_libraries(lgtest LgTerm curses)

