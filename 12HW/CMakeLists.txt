cmake_minimum_required( VERSION 3.10 )
project( homography )

set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package( OpenCV 3 REQUIRED )
message(STATUS "Opencv Version: ${OpenCV_VERSION}")

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( virtualBillboard virtual-billboard.cpp )

target_link_libraries( virtualBillboard ${OpenCV_LIBS} )