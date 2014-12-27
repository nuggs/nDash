cmake_minimum_required(VERSION 2.6)

project(kernel)

add_library(kernel SHARED Plugin.cpp Kernel.cpp)

if (WIN32)
    set_target_properties(kernel PROPERTIES PREFIX "")
endif (WIN32)

