cmake_minimum_required(VERSION 3.10)
project(opencvtest)

set(CMAKE_CXX_STANDARD 17)

# Set this to your OpenCV build folder
set(OpenCV_DIR "C:/Users/arya9/Downloads/opencv/build/x64/vc16")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencvtest main.cpp)
target_link_libraries(opencvtest ${OpenCV_LIBS})
