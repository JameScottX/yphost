cmake_minimum_required (VERSION 2.8)

project (hw_lib)

SET(LIBRARY_OUTPUT_PATH ./release) 
SET(EXECUTABLE_OUTPUT_PATH ./example)

add_compile_options(-Wall  -g -fdiagnostics-color=auto -fPIC)

include_directories(./src ./example)

aux_source_directory(./src DIR_SRC)
aux_source_directory(./example DIR_EXAMPLE)

add_library(slc STATIC ${DIR_SRC})

link_directories(${CMAKE_CURRENT_BINARY_DIR}/release) 

add_executable(slc_test ${DIR_EXAMPLE})
target_link_libraries(slc_test libslc.a -lpthread)

add_dependencies(slc_test slc)

execute_process(COMMAND ${CMAKE_COMMAND} -E
copy "../src/slc.h"  "${LIBRARY_OUTPUT_PATH}/"
)