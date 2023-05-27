cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
add_executable(main main_test.cpp)

add_test(MainTest main)