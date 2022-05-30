cmake_minimum_required(VERSION 3.5)

project(yphost LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()


include_directories( $ENV{MVCAM_COMMON_RUNENV}/../include 
                     slc
                    )
link_directories( $ENV{MVCAM_COMMON_RUNENV}/64 )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message("########## The OpenCV is ok ! ##########")
endif (OpenCV_FOUND)
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(./slc)

add_executable(yphost
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  hkimage.cpp
  hkimage.h
  yuv2rgb.cpp
  yuv2rgb.h
  car.cpp
  car.h
  slc/slc.h
)

target_link_libraries(yphost PRIVATE Qt5::Widgets )
target_link_libraries(yphost PRIVATE ${OpenCV_LIBRARIES})
target_link_libraries(yphost PRIVATE libslc.a -lpthread)
target_link_libraries(yphost PRIVATE libMvCameraControl.so)

