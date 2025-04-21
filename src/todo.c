#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 256

struct Task {
  char *description;
  struct Task *next;
};

/**
 * Function to get the home directory and append the todo file path.
 * @return The full path to the todo file.
 */
char *home_directory() {
  char *getenv(const char *name);
  char *todo_file = "/todo.txt";
  char *home_directory = getenv("HOME");
  if (home_directory == NULL) {
    perror("Failed to get the home directory");
    return NULL;
  }
  strcat(home_directory, todo_file);
  return home_directory;
}

/**
 * Function to add a task to the todo list.
 * @param task The description of the task to be added.
 */
void add_task(const char *task) {
  char *full_path_directory = home_directory();
  FILE *file = fopen(full_path_directory, "a");

  if (file == NULL) {
    perror("Failed to open the file");
    return;
  }
  fprintf(file, "%s\n", task);
  fclose(file);
  printf("Added: %s\n", task);
}

// Function to list all tasks
void list_tasks(void) {
  char *full_path_directory = home_directory();
  FILE *file = fopen(full_path_directory, "r");
  if (file == NULL) {
    perror("Failed to open the file!");
    return;
  }

  char line[MAX_TASK_LENGTH];
  int index = 1;

  // check if the file is empty
  int ch = fgetc(file);
  if (ch == EOF) {
    printf("Your todo list is empty\n");
    fclose(file);
    return;
  }

  // put back the character that was read
  ungetc(ch, file);

  printf("Your Todo List:\n");
  while (fgets(line, sizeof(line), file)) {
    printf("%d. %s", index++, line);
  }
  fclose(file);
}

void removeAllTodos() {
  char *full_path_directory = home_directory();
  FILE *read_file = fopen(full_path_directory, "r");

  int ch = fgetc(read_file);
  if (ch == EOF) {
    printf("Your todo list is already empty\n");
    return;
  }

  // put back the character that was read
  ungetc(ch, read_file);

  FILE *file = fopen(full_path_directory, "w");
  if (file == NULL) {
    perror("Failed to open the temp file");
    return;
  }
  fclose(file);
  fclose(read_file);

  printf("Cleared all todos!\n");
}

/**
 * Function to remove a specific task from the todo list.
 * @param task_num The number of the task to be removed.
 * @return 0 if the task was successfully removed, 1 otherwise.
 */
int remove_task(int task_num) {
  char *full_path_directory = home_directory();
  FILE *file = fopen(full_path_directory, "r");
  if (file == NULL) {
    perror("Failed to open the file");
    return 1;
  }

  FILE *temp_file = fopen("temp.txt", "w");
  if (temp_file == NULL) {
    perror("Failed to open the temp file");
    fclose(file);
    return 1;
  }

  char line[MAX_TASK_LENGTH];
  int index = 1;
  int todo_found = 0;

  while (fgets(line, sizeof(line), file)) {
    if (index == task_num) {
      todo_found = 1;
    } else {
      fputs(line, temp_file);
    }
    index++;
  }

  // If the requested task_num did not exist in the file, show a message
  if (!todo_found) {
    printf("There is no task in that position!\n");
    fclose(file);
    fclose(temp_file);
    remove("temp.txt");
    return 1;
  }

  fclose(file);
  fclose(temp_file);

  remove(full_path_directory);
  rename("temp.txt", full_path_directory);

  printf("Removed task %d\n", task_num);
  return 0;
}

// Function to display the usage of the program
void print_usage(const char *program_name) {
  printf("Usage: %s [add, -a <task>] [list, -l] [remove, -r <task_num>] "
         "[clear, -c]\n",
         program_name);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "-a") == 0) {
    if (argc < 3) {
      printf("Error: Missing task description.\n");
      return 1;
    }
    // Calculate total length required, including spaces between words.
    size_t total_length = 0;
    for (int i = 2; i < argc; i++) {
      total_length += strlen(argv[i]);
      if (i < argc - 1) { // Add one for the space between words
        total_length++;
      }
    }
    // Abort if the combined length would exceed our buffer.
    if (total_length >= MAX_TASK_LENGTH) {
      fprintf(stderr, "Error: Task description is too long.\n");
      return 1;
    }

    // Concatenate the entire task description into one string
    char task[MAX_TASK_LENGTH] = "";
    size_t current_length = 0;
    for (int i = 2; i < argc; i++) {
      size_t arg_len = strlen(argv[i]);
      strcat(task, argv[i]);
      current_length += arg_len;
      // Add a space between each word
      if (i < argc - 1) {
        task[current_length++] = ' ';
      }
    }
    task[current_length] = '\0';
    add_task(task);

  } else if (strcmp(argv[1], "list") == 0 || strcmp(argv[1], "-l") == 0) {
    list_tasks();
  } else if (strcmp(argv[1], "remove") == 0 || strcmp(argv[1], "-r") == 0) {
    if (argc < 3) {
      printf("Error: Missing task number.\n");
      return 1;
    }
    int task_num = atoi(argv[2]);
    // Return early if the user input anything other then a integer
    if (task_num == 0) {
      fprintf(stderr, "Only add numbers!\n");
      return 1;
    }
    remove_task(task_num);
  } else if (strcmp(argv[1], "clear") == 0 || strcmp(argv[1], "-c") == 0) {
    removeAllTodos();
  } else {
    print_usage(argv[0]);
  }

  return 0;
}
