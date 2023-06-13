# set required version of CMake
cmake_minimum_required(VERSION 3.1)

# Set project name
project(ImgProcessingPipe)

# Set the C++ standard to 11
set(CMAKE_CXX_STANDARD 11)

# Setzt die Pfade für die Include- und Lib-Verzeichnisse
set(OpenCV_INCLUDE_DIR /usr/local/include/opencv4)
#set(OpenCV_LIB_DIR /usr/local/lib)
set(Boost_INCLUDE_DIR /usr/local/include)
#set(Boost_LIB_DIR /usr/local/lib)

# Specify that the C++ standard is required
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_PREFIX_PATH "/usr/local/include/boost" ${CMAKE_PREFIX_PATH})


# Find OpenCV and Boost
find_package(OpenCV REQUIRED PATHS ${OpenCV_LIB_DIR})
find_package(Boost REQUIRED COMPONENTS filesystem)


# Include the necessary directories for OpenCV and Boost
include_directories(${OpenCV_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

# Create an executable called "ImgProcessingPipe" using the source files
add_executable(ImgProcessingPipe src/main.cpp src/ProcessImage.cpp)

# Link the executable with the OpenCV and Boost libraries
target_link_libraries(ImgProcessingPipe ${OpenCV_LIBS} ${Boost_LIBRARIES})
