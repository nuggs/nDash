cmake_minimum_required(VERSION 2.6)

add_executable(nDash Core.cpp)
target_link_libraries(nDash kernel)

install(TARGETS nDash DESTINATION bin/)