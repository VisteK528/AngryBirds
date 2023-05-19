cmake_minimum_required(VERSION 3.16)

project(angrybirds)
set(CMAKE_CXX_STANDARD 20)
FILE(GLOB_RECURSE SRC "src/*.cpp")

find_package(SFML COMPONENTS window graphics system audio REQUIRED)
link_directories(box2d/build/bin)

add_executable(
        angrybirds
        main.cpp
        ${SRC}
        src/sound_manager.cpp)

target_link_libraries(angrybirds libbox2d.a)
target_include_directories(angrybirds PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(angrybirds sfml-graphics sfml-window sfml-system sfml-audio)