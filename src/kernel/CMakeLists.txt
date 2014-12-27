cmake_minimum_required(VERSION 2.6)

project(kernel)

add_library(kernel SHARED Plugin.cpp Kernel.cpp)
set_target_properties(kernel PROPERTIES PREFIX "")

install(TARGETS kernel DESTINATION bin/)