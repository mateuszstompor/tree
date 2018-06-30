cmake_minimum_required(VERSION 3.9)
project(aTree VERSION 1.0.0 DESCRIPTION "tree data structure designed to be used in 3D graphics projects")

add_library(aTree INTERFACE)
target_include_directories(aTree INTERFACE ${CMAKE_SOURCE_DIR})
install(FILES tree.hpp DESTINATION include)