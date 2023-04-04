cmake_minimum_required(VERSION 3.24)
project(Get_ip)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(FetchContent)

set (BOOST_ROOT "../Get_ip/boost_1_72_0/")
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)


#find_package(Boost REQUIRED COMPONENTS)
find_package(Boost 1.72.0 COMPONENTS beast asio)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3 -I C:/Users/evgen/CLionProjects/Get_ip/boost_1_72_0/")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")
link_libraries(ws2_32 wsock32)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


add_subdirectory(src)

target_link_libraries(Get_ip nlohmann_json::nlohmann_json)
target_link_libraries(Get_ip ${Boost_LIBRARIES})