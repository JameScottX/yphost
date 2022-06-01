cmake_minimum_required(VERSION 3.0.2)
project(uart)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

include_directories( 
    ./
) 

add_executable(uart ./main.cpp ./uart_op.cpp)
target_link_libraries(uart -lpthread)
