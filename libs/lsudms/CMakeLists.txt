cmake_minimum_required(VERSION 3.15)
project(lsudms VERSION 0.1.0)
set(test libtest)
include_directories(include)
add_library(lsudms STATIC include/lsudms.hpp lsudms.cpp)
add_executable(${test} test.cpp)
target_link_libraries(${test} PRIVATE lsudms)
target_include_directories(${test} PRIVATE
    include
)