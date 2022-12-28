project(rvddt DESCRIPTION "RiscV emulator")
cmake_minimum_required(VERSION 3.12)

#include(lib)

add_subdirectory(lib)

add_executable(rvddt main.cc)
target_link_libraries(rvddt PUBLIC lib_rvddt)

set_property(TARGET rvddt PROPERTY CXX_STANDARD 20)

