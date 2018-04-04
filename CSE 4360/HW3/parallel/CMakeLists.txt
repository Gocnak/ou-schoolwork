cmake_minimum_required(VERSION 3.10)
project(cud CUDA)
find_package(CUDA REQUIRED)

include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

add_executable(cud parallel.h parallel.cu)