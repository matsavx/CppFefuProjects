cmake_minimum_required(VERSION 3.15)
project(fib)

set(CMAKE_CXX_STANDARD 14)

add_executable(fib main.cpp lib.cpp lib.h)