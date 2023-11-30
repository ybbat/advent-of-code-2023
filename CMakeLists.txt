cmake_minimum_required(VERSION 3.25)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)


file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/*)

foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/${SUBDIR})
        add_subdirectory(src/${SUBDIR})
    endif()
endforeach()