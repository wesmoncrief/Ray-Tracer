cmake_minimum_required(VERSION 3.5)
project(RayTracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -ansi -pedantic -O0 -framework GLUT -framework OpenGL")

set(SOURCE_FILES main.cpp)
add_executable(RayTracing ${SOURCE_FILES})