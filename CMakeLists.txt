cmake_minimum_required(VERSION 3.17)
project(beta)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(beta main.cpp brainfuck.cpp brainfuck.h)