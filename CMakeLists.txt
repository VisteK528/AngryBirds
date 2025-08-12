cmake_minimum_required(VERSION 3.16)

project(angrybirds)
set(CMAKE_CXX_STANDARD 20)
FILE(GLOB_RECURSE SRC "src/*.cpp")

#include(CTest)
#enable_testing()
#add_subdirectory(tests)

find_package(SFML COMPONENTS window graphics system audio REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "/home/vistek/local/aether")
find_package(Aether REQUIRED CONFIG) 

add_executable(
        angrybirds
        main.cpp
        ${SRC})

target_link_libraries(angrybirds PRIVATE Aether::Aether)
target_include_directories(angrybirds PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(angrybirds PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)