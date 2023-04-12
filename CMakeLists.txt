cmake_minimum_required(VERSION 3.16)

project(fs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(libzippp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(.)

add_executable(fs main.cpp)
target_link_libraries(fs Boost::program_options OpenSSL::SSL libzippp::libzippp)

add_executable(root root.cpp)
target_link_libraries(root Boost::program_options OpenSSL::SSL libzippp::libzippp)