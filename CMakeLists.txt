cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 14)

project(
    CLIlib
    VERSION 0.9.0
    LANGUAGES CXX
    DESCRIPTION "Small library for implementation command line interface."
)
# Добавьте источник в исполняемый файл этого проекта.
add_library (CLIlib "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h")

add_executable(test "${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp")
target_link_libraries(test PRIVATE CLIlib)
