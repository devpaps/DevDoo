cmake_minimum_required(VERSION 3.10)
project(DevDoo C)

 # Turn on CTest support
 enable_testing()

# Main app
add_executable(todo src/todo.c)

  # … warning flags …

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
 # ——— Test app (built on every platform where CUnit is available) ———
 find_package(CUnit QUIET)        # will only succeed if CUnit is installed
 if(CUnit_FOUND)
   # test executable
   add_executable(test_todo
     tests/test_todo.c
     src/todo.c
   )
   # link in CUnit and your code
   target_link_libraries(test_todo PRIVATE CUnit::CUnit)

   # same warning flags for tests
   if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
     target_compile_options(test_todo PRIVATE -Wall -Wextra -pedantic)
   elseif(MSVC)
     target_compile_definitions(test_todo PRIVATE _CRT_SECURE_NO_WARNINGS)
   endif()

   # register with CTest
   add_test(NAME TodoTests COMMAND test_todo)
 endif()

install(TARGETS todo DESTINATION bin)

