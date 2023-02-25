cmake_minimum_required(VERSION 3.24)
project(minitalk C)

set(CMAKE_C_STANDARD 90)
include_directories(${CMAKE_SOURCE_DIR}/printflibft/include)
add_executable(minitalk main.c server.c client.c)
target_link_libraries(minitalk ${CMAKE_SOURCE_DIR}/printflibft/libft.a)
