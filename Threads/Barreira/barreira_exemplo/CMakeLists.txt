cmake_minimum_required(VERSION 3.16)
project(barreira_exemplo C)

set(CMAKE_C_STANDARD 99)

add_executable(barreira_exemplo
        src/main.c
        src/thread.c)

find_package( Threads REQUIRED)
target_include_directories(barreira_exemplo PRIVATE include)

target_link_libraries(barreira_exemplo Threads::Threads)