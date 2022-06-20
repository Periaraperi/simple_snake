cmake_minimum_required(VERSION 3.10.0)

project(snake_game)

set(SRCS main.cpp snake.cpp snake.hpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(snake ${SRCS})
target_link_libraries(snake ${SDL2_LIBRARIES})
target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic)

