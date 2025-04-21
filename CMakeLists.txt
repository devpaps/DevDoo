cmake_minimum_required(VERSION 3.10)
project(Devdoo C)

# Main app
add_executable(todo src/todo.c)

# Enable warnings for GCC/Clang
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(todo PRIVATE -Wall -Wextra -pedantic)
endif()

# Test app with CUnit
add_executable(test_todo tests/test_todo.c src/todo.c)

# Manually add CUnit includes and link
include_directories(/usr/include/CUnit)
target_link_libraries(test_todo PRIVATE cunit)

# Enable warnings for tests too
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(test_todo PRIVATE -Wall -Wextra -pedantic)
endif()

# Install binary
install(TARGETS todo DESTINATION bin)

