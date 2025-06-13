cmake_minimum_required(VERSION 3.28.3)
project(cpp_playground)

set(CMAKE_CXX_STANDARD 23)

set(SINGLE_FILE_TARGETS_DIR ${CMAKE_SOURCE_DIR}/SingleFileTargets)

## === GTest Setup ===
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("external/googletest-1.17.0")

## === Folder Executables ===


## === Single Source Executables ===
file(GLOB SINGLE_FILE_SRCS
        ${SINGLE_FILE_TARGETS_DIR}/*.cpp
        ${SINGLE_FILE_TARGETS_DIR}/*.c)

foreach(SRC_FILE ${SINGLE_FILE_SRCS})
    get_filename_component(TARGET_NAME ${SRC_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SRC_FILE})

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif ()
endforeach ()

target_link_libraries(gtest_test PRIVATE gtest_main)
target_include_directories(gtest_test PRIVATE gtest)

target_link_libraries(freeglut_test PRIVATE freeglut opengl32) #glu32

target_link_libraries(span_test PRIVATE python3)