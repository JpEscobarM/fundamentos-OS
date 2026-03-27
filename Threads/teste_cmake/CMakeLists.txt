cmake_minimum_required(VERSION 3.10)

project(TesteC C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

add_executable(teste_cmake
   main.c
)

target_include_directories(teste_cmake PRIVATE include)

target_link_libraries(teste_cmake Threads::Threads)
