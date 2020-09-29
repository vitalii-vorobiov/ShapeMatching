cmake_minimum_required(VERSION 3.17)
project(ShapeMatching)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.73.0)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.73.0/lib)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(includes)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ShapeMatching main.cpp includes/CommandLineParser.h src/CommandLineParser.cpp)

target_link_libraries( ShapeMatching ${Boost_LIBRARIES} )
target_link_libraries( ShapeMatching ${OpenCV_LIBS} )
