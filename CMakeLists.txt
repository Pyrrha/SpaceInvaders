cmake_minimum_required(VERSION 3.3)
project(Space_Invaders)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp const.h)
add_executable(Space_Invaders ${SOURCE_FILES})
