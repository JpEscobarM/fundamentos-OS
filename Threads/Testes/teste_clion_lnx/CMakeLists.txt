cmake_minimum_required(VERSION 3.16)
project(teste_clion_lnx C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(teste_clion_lnx
        src/main.c
        src/thread.c)

target_include_directories(teste_clion_lnx PRIVATE include)

target_link_libraries(teste_clion_lnx Threads::Threads)


