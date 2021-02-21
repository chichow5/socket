cmake_minimum_required(VERSION 2.8)

project(Test)

aux_source_directory(. DIR_SRCS)

add_subdirectory(core)

add_executable(m main.cpp)

target_link_libraries(m corefun)