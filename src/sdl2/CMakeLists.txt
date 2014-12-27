cmake_minimum_required(VERSION 2.6)

project(sdl2)
add_library(SDL2 SHARED SDL2Render.cpp)
set_target_properties(SDL2 PROPERTIES PREFIX "")

install(TARGETS SDL2 DESTINATION bin/plugins)