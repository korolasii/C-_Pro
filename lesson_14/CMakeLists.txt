cmake_minimum_required(VERSION 3.15)
project(MathProject)

file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/${child})
        add_subdirectory(src/${child})
    endif()
endforeach()
