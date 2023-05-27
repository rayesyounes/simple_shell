# Simple Shell

This repository contains the source code for a simple Unix shell implementation. The shell is written in C programming language and provides basic command-line functionality, including executing commands, handling input/output redirection, and supporting background processes.

## Features

- Executes commands entered by the user.
- Supports basic command-line syntax, such as command arguments.
- Implements input/output redirection using the '<' and '>' operators.
- Handles background processes using the '&' operator.
- Supports built-in commands, including `cd` for changing directories and `exit` for exiting the shell.
- Displays a prompt for user input.
- Parses and tokenizes user input.

## Getting Started

To get started with the simple shell, follow these steps:

1. Clone the repository:

   ```
   git clone https://github.com/rayesyounes/simple_shell.git
   ```

2. Compile the source code:

   ```
   gcc -Wall -Werror -Wextra -pedantic *.c -o shell
   ```

3. Run the shell:

   ```
   ./shell
   ```

## Usage

Once the shell is running, you can enter commands and interact with it. The basic syntax for running commands is:

```
command [arguments]
```

Some examples of supported commands:

- Running a program:

  ```
  $ ls
  ```

- Changing directories:

  ```
  $ cd path/to/directory
  ```

- Exiting the shell:

  ```
  $ exit
  ```

## Input/Output Redirection

The shell supports input/output redirection using the `<` and `>` operators. These operators allow you to redirect the standard input or output of a command to a file.

- Redirecting input from a file:

  ```
  $ command < input.txt
  ```

- Redirecting output to a file:

  ```
  $ command > output.txt
  ```

## Background Processes

The shell can run commands in the background using the `&` operator. This allows you to execute multiple commands simultaneously.

- Running a command in the background:

  ```
  $ command &
  ```

## Built-in Commands

The shell provides some built-in commands that are executed directly by the shell itself.

- Changing directories using `cd`:

  ```
  $ cd path/to/directory
  ```

- Exiting the shell using `exit`:

  ```
  $ exit
  ```
## Screenshots

![Spoutnikrs Unix-shell](/Screenshot/Shell-screenshot.png)

## Limitations

- The shell does not support complex features found in advanced shells, such as piping, command substitution, and shell scripting.
- Error handling and input validation are limited in this simple implementation.

## Contributing

Contributions to the simple shell are welcome. If you find a bug or have an enhancement in mind, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Acknowledgments

The simple shell was developed as part of a programming exercise and is inspired by the Unix shell. Special thanks to the contributors and the open-source community for their valuable resources and support.
