cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Add the executable
add_executable(todo src/todo.c)

# Enable warnings for GCC/Clang
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(todo PRIVATE -Wall -Wextra -pedantic)
endif()

add_executable(test_todo tests/test_todo.c src/todo.c)
target_link_libraries(test_todo PRIVATE cunit)

install(TARGETS todo DESTINATION bin)
