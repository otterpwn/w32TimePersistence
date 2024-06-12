cmake_minimum_required(VERSION 3.28)
project(w32TimePersistence)

set(CMAKE_CXX_STANDARD 17)

add_library(w32TimePersistence SHARED library.cpp)
