cmake_minimum_required(VERSION 3.16)

project(homework02)

# 添加 Eigen 头文件
include_directories("/usr/include/eigen3")
add_executable(useMatrix useMatrix.cpp)