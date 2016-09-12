cmake_minimum_required(VERSION 3.5)
project(FirstTask)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -lpthread")

set(SOURCE_FILES main.c generator.c generator.h)
add_executable(FirstTask ${SOURCE_FILES})