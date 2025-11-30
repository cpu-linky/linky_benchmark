cmake_minimum_required(VERSION 3.19.0)
project(cstate_monitor VERSION 0.1.0 LANGUAGES C)

add_executable(cstate_monitor main.c)

include(CTest)
enable_testing()

