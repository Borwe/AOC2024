cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(AOC2024
        LANGUAGES C
        VERSION 0.1.0)

set(CMAKE_EXPOERT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ./src/hello.c)
