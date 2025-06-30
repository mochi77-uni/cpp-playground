
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
