cmake_minimum_required(VERSION 3.20)
project(Magazine_subscribe C)

set(CMAKE_C_STANDARD 99)

add_executable(Magazine_subscribe main.c mag.h)
add_executable(test test.c)
