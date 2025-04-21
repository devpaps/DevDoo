#include "../src/todo.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

void test_add_task(void) {
  add_task("Test Task 1");
  FILE *file = fopen(home_directory(), "r");
  CU_ASSERT_PTR_NOT_NULL(file);

  char line[MAX_TASK_LENGTH];
  char *ret = fgets(line, sizeof(line), file);

  CU_ASSERT_PTR_NOT_NULL(ret);
  CU_ASSERT_STRING_EQUAL(line, "Test Task 1\n");

  fclose(file);
}

void test_list_tasks(void) {
  add_task("Task 1");
  add_task("Task 2");

  FILE *file = fopen(home_directory(), "r");
  CU_ASSERT_PTR_NOT_NULL(file);

  char line[MAX_TASK_LENGTH];
  char *ret = fgets(line, sizeof(line), file);

  CU_ASSERT_PTR_NOT_NULL(ret);
  CU_ASSERT_STRING_EQUAL(line, "Task 1\n");

  char *ret2 = fgets(line, sizeof(line), file);
  CU_ASSERT_PTR_NOT_NULL(ret2);
  CU_ASSERT_STRING_EQUAL(line, "Task 2\n");

  fclose(file);
}

void test_remove_task(void) {
  add_task("Task to Remove");
  int result = remove_task(1);
  CU_ASSERT_EQUAL(result, 0);

  FILE *file = fopen(home_directory(), "r");
  CU_ASSERT_PTR_NOT_NULL(file);

  int ch = fgetc(file);
  CU_ASSERT_EQUAL(ch, EOF);

  fclose(file);
}

void test_clear_tasks(void) {
  add_task("Task 1");
  add_task("Task 2");
  removeAllTodos();

  FILE *file = fopen(home_directory(), "r");
  CU_ASSERT_PTR_NOT_NULL(file);

  int ch = fgetc(file);
  CU_ASSERT_EQUAL(ch, EOF);

  fclose(file);
}
