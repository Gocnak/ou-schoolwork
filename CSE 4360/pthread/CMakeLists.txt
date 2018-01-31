cmake_minimum_required(VERSION 3.9)
project(pthread C)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(pthread main.c)

target_link_libraries(pthread Threads::Threads)