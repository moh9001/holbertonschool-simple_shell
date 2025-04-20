#include "shell.h"

/**
 * handle_builtins - Handles built-in commands
 * @args: Array of arguments
 * @program_name: Name of the program
 * @env: Environment variables
 * @last_status: Last command's exit status
 * @builtin_handled: Pointer to flag indicating if built-in was handled
 * Return: Status of the built-in command
 */
int	handle_builtins(char **args, char *program_name, char **env
		, int last_status, int *builtin_handled)
{
	int	i;

	(void)program_name;
	if (!args || !args[0])
		return (0);
	if (strcmp(args[0], "exit") == 0)
	{
		*builtin_handled = 1;
		return (last_status);
	}
	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		*builtin_handled = 1;
		return (1);
	}
	return (0);
}
