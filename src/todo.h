#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#define MAX_TASK_LENGTH 256

void add_task(const char *task);
void list_tasks(void);
void removeAllTodos(void);
int remove_task(int task_num);
void print_usage(const char *program_name);
const char *home_directory(void);

#endif
