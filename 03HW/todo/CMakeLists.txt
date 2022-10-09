cmake_minimum_required(VERSION 2.8)
project(cppNewFeather)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} cppNewFeather_answer.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})