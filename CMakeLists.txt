cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
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
    VERSION 0.9.4.4
    LANGUAGES CXX
    DESCRIPTION "Small library for implementation command line interface."
)

add_library (CLIlib "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h")

# if CLIlib was built ad master project the include folder will be generated of refreshed automatically
if(CLI_MASTER_PROJECT)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif()
    # after building library, header file will be copied into include directory
    add_custom_command(
        TARGET CLIlib POST_BUILD
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h ${CMAKE_CURRENT_SOURCE_DIR}/include/CLIlib.h
    )
    add_executable(run_tests "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/test.cpp")
    target_link_libraries(run_tests PRIVATE CLIlib gtest)

    # after building tests, they will start automatically
    add_custom_command(
        TARGET run_tests POST_BUILD
        COMMAND ${CMAKE_BINARY_DIR}/run_tests
    )
endif()
