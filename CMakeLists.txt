cmake_minimum_required(VERSION 3.23)
project(miniSTL)

set(CMAKE_CXX_STANDARD 11)

add_executable(miniSTL miniSTL/main.cpp miniSTL/Vector.h miniSTL/Vector.cpp)
