cmake_minimum_required(VERSION 2.8)

project(nDash)

add_definitions(-Wall -ggdb -std=c++11)

if (UNIX)
    add_definitions(-fPIC)
endif (UNIX)

add_subdirectory(src)