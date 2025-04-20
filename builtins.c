#include "shell.h"

/**
 * handle_builtins - Handles built-in commands
 * @args: Array of arguments
 * @program_name: Name of the program
 * @env: Environment variables
 * Return: 1 if built-in handled, 0 otherwise
 */
int	handle_builtins(char **args, char *program_name, char **env)
{
	int	i;

	(void)program_name;
	if (strcmp(args[0], "exit") == 0)
	{
		free_array(args);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		free_array(args);
		return (1);
	}
	return (0);
}
