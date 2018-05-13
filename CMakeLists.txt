cmake_minimum_required(VERSION 2.6)

project(6lab)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(SOURCE1_EXE src/patterns_search.cpp)
set(SOURCE2_EXE src/wild_card.cpp)
set(SOURCE_LIB1 src/aho_corasick.cpp)
set(SOURCE_LIB2 src/wildcard_functions.cpp)

add_library(aho_corasick STATIC ${SOURCE_LIB1})
add_library(wc_func STATIC ${SOURCE_LIB2})

add_executable(ps ${SOURCE1_EXE})
target_link_libraries(ps aho_corasick)
add_executable(joker ${SOURCE2_EXE})
target_link_libraries(joker aho_corasick wc_func)

add_subdirectory(test)