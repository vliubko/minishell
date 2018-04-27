# minishell
The objective of this project is for you to create the simplest start of a shell script. <br>
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

## Installation and usage

### Tested only on MacOS

### Building the program

1. Download this repository
	
`git clone --recurse-submodules https://github.com/vliubko/minishell.git`

2. `cd` into the root directory and run `make`

`cd minishell && make`

### Running the program

After building the source, run `./minishell` from the project root directory.

### Mandatory

- Can only use C
- Must respect the school imposed coding style ([The Norm](https://cdn.intra.42.fr/pdf/pdf/1065/norme.en.pdf))
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use [Libft](https://github.com/vliubko/libft/)
- Handle program interruption (Ctrl + D)

### Bonuses

- Signal management (specifically Ctrl + C)
- PATH's right management (error handling)
- Multiple commands (semi colons)
