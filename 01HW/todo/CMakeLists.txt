cmake_minimum_required(VERSION 3.10)
project(hw01)
FIND_PACKAGE(OpenCV REQUIRED)
# 添加头文件
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
# 主要用sprintf
ADD_EXECUTABLE( ${PROJECT_NAME} hw01.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})

add_executable(homework1 homework1.cpp)        
# 链接OpenCV库
target_link_libraries( homework1 ${OpenCV_LIBS})

# 添加fmt库
add_subdirectory(dependency/fmt EXCLUDE_FROM_ALL)
target_link_libraries(homework1 fmt-header-only)