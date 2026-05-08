*This project has been created as part of the 42 curriculum by [adarolla aka JEAN MOULIN] [mabenois aka DE GAULLE].*

# Minishell

## Description

Minishell is a simplified reimplementation of a Unix shell. The goal of this project is to understand how shells work internally by recreating key features such as command parsing, process creation, piping, and redirection.

This project focuses on:

* Parsing user input into tokens
* Executing built-in and external commands
* Managing processes using `fork`, `execve`, and `wait`
* Handling pipes and file redirections
* Managing environment variables
* Handling signals (e.g., `Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

Through this project, we explore low-level system programming concepts in C, especially how the operating system interacts with processes and file descriptors.

---

## Features

* Execution of basic commands (e.g., `ls`, `echo`, `pwd`)
* Built-in commands:

  * `cd`
  * `echo`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`
* Pipes (`|`)
* Input/output redirections (`<`, `>`, `>>`)
* Environment variable expansion (`$VAR`)
* Signal handling similar to Bash behavior
* Error management and exit status handling

---

## Instructions

### Compilation

Clone the repository and compile using `make`:

```bash
git clone <your-repo-url>
cd minishell
make
```

Available rules:

```bash
make        # compile the project
make clean  # remove object files
make fclean # remove object files and binary
make re     # recompile everything
```

### Execution

Run the shell with:

```bash
./minishell
```

You will then be able to type commands as in a standard shell.

### Example Usage

```bash
minishell$ echo Hello World
Hello World

minishell$ ls | grep .c
main.c
parser.c

minishell$ cat < infile.txt > outfile.txt
```

---

## Technical Choices

* Written in C using only authorized functions
* Use of linked lists for token and environment management
* Modular architecture:

  * Lexer (tokenization)
  * Parser (structure creation)
  * Executor (command execution)
* File descriptor duplication with `dup2` for redirections and pipes
* Careful memory management to avoid leaks

---

## Challenges Faced

* Correctly parsing complex command inputs
* Handling multiple pipes and redirections simultaneously
* Managing signals without breaking interactive behavior
* Avoiding memory leaks, especially with dynamic structures
* Reproducing Bash-like behavior accurately

---

## Resources

### Documentation & References

* The Linux Programming Interface — Michael Kerrisk
* Advanced Programming in the UNIX Environment — W. Richard Stevens
* Bash manual:
  https://www.gnu.org/software/bash/manual/
* man pages:

  ```bash
  man fork
  man execve
  man pipe
  man dup2
  man wait
  ```

### Tutorials

* Process and pipes in C:
  https://www.geeksforgeeks.org/pipe-system-call/
* Shell implementation basics:
  https://brennan.io/2015/01/16/write-a-shell-in-c/

### AI Usage

AI tools were used during this project for:

* Understanding complex concepts (process management, parsing strategies)
* Debugging specific issues (segmentation faults, memory leaks)
* Clarifying behavior of system calls and edge cases
* Structuring the project and improving code readability

All code was written and validated manually. AI was used as a learning assistant, not as a code generator.

---

## Author(s)

* Adam Rolland-Ternoi
* Manech Benoist Valin 
*

---

## Notes

This project is a pedagogical implementation and does not aim to fully replicate Bash. Some advanced features (such as job control or wildcards) may not be implemented.

