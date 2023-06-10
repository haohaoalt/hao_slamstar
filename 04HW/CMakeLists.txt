cmake_minimum_required(VERSION 3.12)
project(homework_4)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV REQUIRED)
add_executable(homework_4 homework_4.cpp)
target_link_libraries(homework_4 ${OpenCV_LIBS})