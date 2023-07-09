cmake_minimum_required(VERSION 3.15.3)
project(Noise)

set(CMAKE_CXX_STANDARD 11)

add_executable(Noise main.cpp PerlinNoise.cpp PerlinNoise.h ppm.cpp ppm.h)