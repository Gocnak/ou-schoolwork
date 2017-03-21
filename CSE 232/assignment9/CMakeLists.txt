cmake_minimum_required(VERSION 3.6)
project(assignment9)

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

FILE(GLOB sources main.cpp
        ../GUI/*.cpp
        ../GUI/*.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfltk")
add_executable(assignment9 ${sources})
TARGET_LINK_LIBRARIES(assignment9 fltk fltk_images)