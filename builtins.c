#include "shell.h"

/**
 * handle_builtins - Handles built-in commands
 * @args: Array of arguments
 * @program_name: Name of the program
 * @env: Environment variables
 * @last_status: Last command's exit status
 * Return: 1 if built-in handled, last_status for exit, 0 otherwise
 */
int handle_builtins(char **args, char *program_name, char **env
		, int last_status)
{
	int	i;

	(void)program_name;
	if (strcmp(args[0], "exit") == 0)
		return (last_status);
	else if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		return (1);
	}
	return (0);
}
