cmake_minimum_required(VERSION 3.5.0)
project(demo1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}  
                          "~/usr/lib/cmake/opencv4/"
)

find_package( OpenCV 4.1.0 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")
add_executable( test test.cpp )
target_link_libraries( test ${OpenCV_LIBS} )
