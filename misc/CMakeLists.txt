cmake_minimum_required(VERSION 3.5)

project(Test LANGUAGES CXX)

# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")



find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message("########## The OpenCV is ok ! ##########")
endif (OpenCV_FOUND)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(img_get
img_get.cpp

)

target_link_libraries(img_get  ${OpenCV_LIBRARIES})


