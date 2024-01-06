cmake_minimum_required(VERSION 3.27)
project(dpool)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp ThreadPool.hpp)
