cmake_minimum_required(VERSION 2.6)

add_executable(nDash Core.cpp)
target_link_libraries(nDash kernel)
if (UNIX)
    target_link_libraries(nDash dl)
endif (UNIX)

install(TARGETS nDash DESTINATION bin/)
