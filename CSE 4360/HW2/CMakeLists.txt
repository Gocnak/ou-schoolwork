cmake_minimum_required(VERSION 3.9)
project(HW2 C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c hashmap.c hashmap.h)

add_executable(HW2 ${SOURCE_FILES})