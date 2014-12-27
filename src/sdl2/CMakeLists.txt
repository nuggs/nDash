cmake_minimum_required(VERSION 2.6)

project(sdl2)
add_library(SDL2 SHARED SDL2Render.cpp)

if (WIN32)
    set_target_properties(SDL2 PROPERTIES PREFIX "")
endif (WIN32)

install(TARGETS SDL2 DESTINATION plugins)
