cmake_minimum_required(VERSION 3.0.2)
project(mec_dev)

# aux_source_directory(./) 

include_directories( 
    .
    ./slc/include
) 

link_directories(./slc)

add_executable(mec_dev cam.cpp)

find_package(OpenCV REQUIRED)



if (OpenCV_FOUND)
    message("########## The OpenCV is ok ! ##########")
endif (OpenCV_FOUND)


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(mec_dev ${OpenCV_LIBRARIES})
target_link_libraries(mec_dev libslc.a -lpthread)




