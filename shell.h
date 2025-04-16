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

#endif /* SHELL_H */
