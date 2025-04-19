#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Environment variable */
extern char **environ;

/* Core functions */
int execute_command(char *line);

/* Utility functions */
char **tokenize(char *line);
char *find_command(char *cmd);
void print_env(void);
int is_whitespace(const char *str);
char *trim_spaces(char *str);

#endif /* SHELL_H */
