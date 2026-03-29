cmake_minimum_required(VERSION 4.1)
project(FIFO C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(FIFO main.c)

target_link_libraries(FIFO Threads::Threads)