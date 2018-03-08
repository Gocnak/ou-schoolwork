cmake_minimum_required(VERSION 3.9)
project(HW2 C)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads)

set(SOURCE_FILES problem-1.c problem-2.c hashmap.c hashmap.h priority_queue.c priority_queue.h map.c map.h set.c set.h utils.c utils.h)

add_definitions(-DPROBLEM_2)

add_executable(HW2 ${SOURCE_FILES})

target_link_libraries(HW2 ${CMAKE_THREAD_LIBS_INIT})