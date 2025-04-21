cmake_minimum_required(VERSION 3.10)
project(DevDoo C)

# Main app
add_executable(todo src/todo.c)

# Warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(todo PRIVATE -Wall -Wextra -pedantic)
endif()

if(MSVC)
  target_compile_definitions(todo PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(UNIX)
# Test app
add_executable(test_todo tests/test_todo.c src/todo.c)

# Link CUnit—once libcunit1-dev is installed, the compiler will find the headers automatically
target_link_libraries(test_todo PRIVATE cunit)

# Same warnings for tests
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(test_todo PRIVATE -Wall -Wextra -pedantic)
endif()
endif()

install(TARGETS todo DESTINATION bin)

