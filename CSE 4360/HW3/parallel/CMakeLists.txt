cmake_minimum_required(VERSION 3.10)
project(cud CUDA)
find_package(CUDA REQUIRED)

add_executable(cud parallel_cublas.cu)
cuda_add_cublas_to_target(cud)