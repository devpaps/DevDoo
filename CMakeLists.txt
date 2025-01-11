cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Add the executable
add_executable(todo todo.c)

# Enable warnings for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(todo PRIVATE -Wall -Wextra -pedantic)
endif()

install(TARGETS todo DESTINATION bin)
