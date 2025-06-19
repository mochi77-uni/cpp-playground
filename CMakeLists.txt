cmake_minimum_required(VERSION 3.28.3)
project(cpp_playground)

set(CMAKE_CXX_STANDARD 23)

set(SINGLE_FILE_TARGETS_DIR ${CMAKE_SOURCE_DIR}/SingleFileTargets)

## === GTest Setup ===
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("external/googletest")

## === General use function ===
function(enable_module target)
    # Enable C++ modules support
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE -fmodules-ts)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${target} PRIVATE -fmodules)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE /experimental:module)
    endif()
endfunction()

## === Folder Executables ===
add_library(module_test_math)
target_sources(module_test_math
        PUBLIC
        FILE_SET CXX_MODULES FILES
        module_test/math.cppm
)

add_executable(module_test module_test/main.cpp)
enable_module(module_test)
target_link_libraries(module_test PRIVATE module_test_math)
add_dependencies(module_test module_test_math)

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