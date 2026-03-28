cmake_minimum_required(VERSION 3.6)
project(mutex_recursivo C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(mutex_recursivo
            src/mutexrecursivo.c)

target_include_directories(mutex_recursivo PRIVATE include)

target_link_libraries(mutex_recursivo Threads::Threads)