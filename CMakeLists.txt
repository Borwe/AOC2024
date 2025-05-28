cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(AOC2024
        LANGUAGES C
        VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SANITIZE_FLAGS -fsanitize=address,undefined)
set(COMPILE_FLAGS -Wall -Wextra -Werror -std=c17)

add_executable(${PROJECT_NAME} ./src/hello.c)

function(create_day_target target_name source_file day_file)
        add_executable(${target_name} ${source_file})
        target_compile_options(${target_name} PRIVATE ${COMPILE_FLAGS} ${SANITIZE_FLAGS})
        target_link_options(${target_name} PRIVATE ${SANITIZE_FLAGS} -lubsan)
        add_custom_target(day${target_name}
                COMMAND ${target_name} ${day_file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

        )
endfunction()

create_day_target(1 ./src/day1.c ./data/day1.txt)
create_day_target(1.5 ./src/day1.5.c ./data/day1.txt)
create_day_target(2 ./src/day2.c ./data/day2.txt)
create_day_target(2.5 ./src/day2.5.c ./data/day2.txt)
create_day_target(3 ./src/day3.c ./data/day3.txt)
create_day_target(3.5 ./src/day3.5.c ./data/day3.txt)

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
