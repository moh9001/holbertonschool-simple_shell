#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function prototypes */
void	display_prompt(void);
char	*read_line(void);
void	execute_command(char *command, char *program_name, char **env);
void	print_error(char *program_name, char *command);
char	**parse_command(char *line);
void	free_array(char **array);

#endif /* SHELL_H */
