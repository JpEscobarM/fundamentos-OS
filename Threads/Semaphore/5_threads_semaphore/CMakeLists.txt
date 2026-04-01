cmake_minimum_required(VERSION 3.16)
project(5_threads_semaphore C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(5_threads_semaphore main.c)

target_link_libraries(5_threads_semaphore Threads::Threads)