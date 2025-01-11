cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(CLI_MASTER_PROJECT ON)
    message(STATUS "CLIlib will be built as master project")
    message(STATUS "CLIlib build type is: ${CMAKE_BUILD_TYPE}")
endif()


project(
    CLIlib
    VERSION 0.9.4.1
    LANGUAGES CXX
    DESCRIPTION "Small library for implementation command line interface."
)

add_library (CLIlib "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h")

# if CLIlib was built ad master project the include folder will be generated of refreshed automatically
if(CLI_MASTER_PROJECT)

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif()

    add_custom_command(
        TARGET CLIlib POST_BUILD
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h ${CMAKE_CURRENT_SOURCE_DIR}/include/CLIlib.h
    )
    add_executable(test "${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp")
    target_link_libraries(test PRIVATE CLIlib)
endif()
