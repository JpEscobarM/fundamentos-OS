cmake_minimum_required(VERSION 3.6)
project(problema_dos_5_filosofos C)

set(CMAKE_C_STANDARD 99)

find_package( Threads REQUIRED)

add_executable(problema_dos_5_filosofos main.c)

target_link_libraries(problema_dos_5_filosofos Threads::Threads)