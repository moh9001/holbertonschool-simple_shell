#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

void	display_prompt(void);
char	*read_line(void);
int	execute_command(char *command, char *program_name
		, char **env, int last_status);
char	**parse_command(char *line);
char	*find_command(char *command, char **env);
void	print_error(char *program_name, char *command);
void	free_array(char **array);
int	handle_builtins(char **args, char *program_name, char **env
		, int last_status, int *builtin_handled);
int	has_non_whitespace(char *str);

#endif
