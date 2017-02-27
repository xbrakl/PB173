cmake_minimum_required(VERSION 3.6)
project(task01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

set(SOURCE_FILES main.cpp)
add_executable(task01 ${SOURCE_FILES})

# adding mbed TLS library
include_directories(SYSTEM mbedtls/include)
add_subdirectory(mbedtls)