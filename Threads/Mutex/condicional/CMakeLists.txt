cmake_minimum_required(VERSION 4.1)
project(codition C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(codition
        src/main.c)

target_link_libraries(condition Threads::Threads)