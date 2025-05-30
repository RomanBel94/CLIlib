﻿cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# check if CLIlib is buildig as master project of subproject
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(CLI_MASTER_PROJECT ON)
    message(STATUS "CLIlib will be built as master project")
    message(STATUS "CLIlib build type is: ${CMAKE_BUILD_TYPE}")

    # add googletest directory
    enable_testing()
    set(BUILD_GMOCK OFF)
    message(STATUS "Tests will be built and run automatically")
    add_subdirectory(${CMAKE_SOURCE_DIR}/googletest)
endif()


project(
    CLIlib
    VERSION 0.9.6
    LANGUAGES CXX
    DESCRIPTION "Small library for implementation command line interface."
)

if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC AND NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    message(FATAL "Compiler: ${CMAKE_CXX_COMPILER_ID} is not supported")
endif()

#main library target
add_library (CLIlib 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h"
)
target_compile_options(CLIlib PRIVATE -fanalyzer)

# if CLIlib is builing as master project the include and lib
# directories will be generated of refreshed automatically
if(CLI_MASTER_PROJECT)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif()
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    endif()
    # after building library, header file will be copied into include directory
    add_custom_command(
        TARGET CLIlib POST_BUILD
        COMMAND cp
        ARGS ${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h ${CMAKE_CURRENT_SOURCE_DIR}/include/CLIlib.h
        
        COMMAND cp
        ARGS ${CMAKE_CURRENT_BINARY_DIR}/*CLIlib* ${CMAKE_CURRENT_SOURCE_DIR}/lib/
    )

    # target for tests
    add_executable(run_tests "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/test.cpp")
    # settings for tests target
    target_include_directories(run_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
    )
    target_link_libraries(run_tests PRIVATE
        CLIlib
        gtest
        gtest_main
    )

    # after building tests, they will start automatically
    add_custom_command(
        TARGET run_tests POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tests
    )
endif()
