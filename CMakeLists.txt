cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(test6 CXX)

find_package (Threads)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

