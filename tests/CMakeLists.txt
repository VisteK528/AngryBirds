cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS window graphics system audio REQUIRED)
link_directories(../box2d/build/bin)
get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

FILE(GLOB_RECURSE SRC "../src/*.cpp")

add_executable(main main_test.cpp ${SRC})

target_link_libraries(main libbox2d.a)
target_link_libraries(main sfml-graphics sfml-window sfml-system sfml-audio)

add_test(MainTest main ${PARENT_DIR})