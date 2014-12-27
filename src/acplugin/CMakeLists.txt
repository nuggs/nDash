cmake_minimum_required(VERSION 2.6)

project(ACPlugin)

add_library(ACPlugin SHARED ACPlugin.cpp)
if (WIN32)
    set_target_properties(ACPlugin PROPERTIES PREFIX "")
    target_link_libraries(ACPlugin ws2_32)
endif (WIN32)

install(TARGETS ACPlugin DESTINATION plugins)
