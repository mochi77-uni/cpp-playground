cmake_minimum_required(VERSION 3.28.3)
project(cpp_playground)

set(CMAKE_CXX_STANDARD 23)

## === External dependencies ===
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("external/googletest")

## === Include cmake utilities ===
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utils)

## === Multi-file examples
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)

## === Auto-configured single-file examples ===
set(SINGLE_FILE_TARGETS_DIR "${CMAKE_SOURCE_DIR}/playground")
file(GLOB_RECURSE SINGLE_FILE_SRCS
        "${SINGLE_FILE_TARGETS_DIR}/*.cpp"
        "${SINGLE_FILE_TARGETS_DIR}/*.c"
)

foreach(SRC_FILE ${SINGLE_FILE_SRCS})
    get_filename_component(TARGET_NAME ${SRC_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SRC_FILE})

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++exp)
    endif ()
endforeach ()

# === special target configurations ===

if (TARGET gtest_test)
    target_link_libraries(gtest_test PRIVATE gtest_main)
    target_include_directories(gtest_test PRIVATE gtest)
endif ()

if (TARGET freeglut_test)
    target_link_libraries(freeglut_test PRIVATE freeglut opengl32) #glu32
endif ()

if (TARGET span_test)
    target_link_libraries(span_test PRIVATE python3)
endif ()
