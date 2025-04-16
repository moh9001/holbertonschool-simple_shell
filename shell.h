#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Function prototype */
void execute_command(char *line);
char **tokenize(char *line);
char *find_command(char *cmd);
void print_env(void);

#endif /* SHELL_H */
