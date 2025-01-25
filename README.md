# Simple todo manager called "DevDoo"

This is simple todo manager that I've built in C. It's a simple command line tool that allows you to add, list, and remove tasks from a todo list.
The saved `.txt` file is stored in the home directory of the user. This implies for Linux users only at the moment.

I named it DevDoo because I'm a developer and it's a todo manager. I'm not very creative with names. :)

## How to install and use it

```bash
$ git clone
$ cd todo
$ cmake ..
$ make
$ sudo make install
$ ./todo add "Buy some milk"
$ ./todo list
$ ./todo remove 1
```

## What is left to be done?

### General Stuff

- [x] Add dynamic home directory check
- [] Add date for when it was created and updated
- [] Encryption for the todo.txt file, OpenSSL?
- [] Add a `--help` flag to show the help message
- [] Colorized Output
- [] Audit Log??
- [] Tests - https://github.com/ThrowTheSwitch/Unity
- [] Rename the toll to just "td" for a fast typeout in the terminal
- [] Consider publishing it to package managers like dnf, apt, or brew, if it get popular enough

### Command-Line Arguments

Enable the app to accept arguments like:

- [x] add <task>
- [x] list
- [x] remove <task_id>
- [x] clear

Do i even need this?

- [] complete <task_id>

---

### Configurable Storage Path

- [] Make the file storage path configurable via a settings file or environment variable. This would be especially useful for users who want to sync the file across devices using cloud storage?
