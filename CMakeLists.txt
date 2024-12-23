cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)

project(
    CLIlib
    VERSION 0.9.2
    LANGUAGES CXX
    DESCRIPTION "Small library for implementation command line interface."
)

add_library (CLIlib "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_command(
        TARGET CLIlib POST_BUILD
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h ${CMAKE_CURRENT_SOURCE_DIR}/include/CLIlib.h
    )

    add_executable(test "${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp")
    target_link_libraries(test PRIVATE CLIlib)
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/CLIlib.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/CLIlib.h)
endif()
