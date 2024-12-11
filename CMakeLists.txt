cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(AOC2024
        LANGUAGES C
        VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ./src/hello.c)

add_custom_target(run ALL
        DEPENDS ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

if(${CMAKE_EXPORT_COMPILE_COMMANDS})
        add_custom_target(cfg ALL
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json
                COMMENT "Copying compile_commands.json from build to root"
        )
endif()
