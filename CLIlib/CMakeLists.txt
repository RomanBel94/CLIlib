# CMakeList.txt: проект CMake для CLIlib; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_library (CLIlib "CLIlib.cpp" "CLIlib.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CLIlib PROPERTY CXX_STANDARD 14)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_executable("test" main.cpp)
target_link_libraries("test" PRIVATE CLIlib)