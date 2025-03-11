cmake_minimum_required(VERSION 3.30)
project(terminal_snake)

set(CMAKE_CXX_STANDARD 23)

add_executable(terminal_snake main.cpp
        "game_logic.cpp"
        "game_logic.h")
