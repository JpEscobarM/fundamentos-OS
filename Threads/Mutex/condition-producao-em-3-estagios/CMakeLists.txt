cmake_minimum_required(VERSION 4.1)
project(prod C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(prod src/main.c)

target_link_libraries(prod Threads::Threads)