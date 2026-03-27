cmake_minimum_required(VERSION 3.6)
project(race_condition C)

set(CMAKE_C_STANDARD 99)


find_package(Threads REQUIRED)

add_executable(race_condition
        src/main.c
        src/thread.c)

target_include_directories(race_condition PRIVATE include)

target_link_libraries(race_condition Threads::Threads)