cmake_minimum_required(VERSION 3.10)
project(HW3 C)
set(CMAKE_C_STANDARD 99)

add_executable(HW3 main.c serial.h serial.c utils.c utils.h)