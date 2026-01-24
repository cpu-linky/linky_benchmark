cmake_minimum_required(VERSION 3.19.0)
project(cstate_monitor VERSION 0.1.0 LANGUAGES C)

add_executable(cstate_monitor 
main.c 
src/load/cpu_load.c
src/load/io_load.c
src/load/memory_load.c)

include(CTest)
enable_testing()

target_link_libraries(cstate_monitor PRIVATE m)