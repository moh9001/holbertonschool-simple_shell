# Simple Shell

A simple UNIX command line interpreter written in C for Holberton School.

## Description

This project implements a basic shell (`hsh`) that mimics some functionalities of `/bin/sh`. It supports:
- Interactive and non-interactive modes
- Command execution with arguments
- PATH handling
- Built-in commands: `exit`, `env`
- Error handling similar to `/bin/sh`

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

Interactive mode:

./hsh
($) /bin/ls
dir1 dir2 file1
($) exit

Non-interactive mode:


echo "/bin/ls" | ./hsh

## Files

- shell.h: Header file with function prototypes and macros.
- main.c: Entry point and main loop.
- prompt.c: Prompt display and input handling.
- parse.c: Command parsing.
- execute.c: Command execution.
- path.c: PATH handling.
- builtins.c: Built-in command implementations.
- error.c: Error handling.
- utils.c: Utility functions.

## Authors
See AUTHORS file.
