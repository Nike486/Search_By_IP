cmake_minimum_required(VERSION 3.24)

include_directories("../include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(Get_ip main.cpp)