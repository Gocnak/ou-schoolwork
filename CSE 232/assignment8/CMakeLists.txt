cmake_minimum_required(VERSION 3.6)
project(assignment8)

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        GUI/Graph.cpp
        GUI/Graph.h
        GUI/GUI.h
        GUI/GUI.cpp
        GUI/Window.h
        GUI/Window.cpp
        GUI/Simple_window.h
        GUI/Simple_window.cpp
        GUI/Point.h
        GUI/std_lib_facilities.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfltk")
add_executable(assignment8 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(assignment8 fltk fltk_images)