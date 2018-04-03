cmake_minimum_required(VERSION 3.10)
option(ENABLE_CUDA "Enable the cuda build" ON)

if(ENABLE_CUDA)
    add_definitions(-DENABLE_CUDA)
    add_subdirectory(parallel)
else()
    add_subdirectory(serial)
endif()