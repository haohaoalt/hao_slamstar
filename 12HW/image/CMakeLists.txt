cmake_minimum_required( VERSION 3.10 )
project(image)

set( CMAKE_CXX_FLAGS "-std=c++11" )
set(OpenCV_DIR "/home/slam007/app/opencv3.4.5/opencv/build")
set(OpenCV_INCLUDE_DIRS "/home/slam007/app/opencv3.4.5/install/include")

find_package( OpenCV REQUIRED )
MESSAGE(STATUS "OpenCV version: "${OpenCV_VERSION})
MESSAGE(${PROJECT_SOURCE_DIR})
MESSAGE(${PROJECT_BINARY_DIR})

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imagemerge image.cpp )

target_link_libraries( imagemerge ${OpenCV_LIBS} )