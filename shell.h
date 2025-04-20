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
int	execute_command(char *command, char *program_name, char **env);
void	fork_and_exec(char **args, char *full_path, char *program_name,
		char **env, int *status);
void	print_error(char *program_name, char *command);
char	**parse_command(char *line);
void	count_args(char *line, int *arg_count);
void	store_args(char *line, char **args, int arg_count);
void	free_array(char **array);
char	*find_command(char *command, char **env);
char	*check_absolute_path(char *command);
char	*search_path(char *command, char **env);
int	handle_builtins(char **args, char *program_name, char **env);

#endif /* SHELL_H */
