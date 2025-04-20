#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: Command to execute
 * @program_name: Name of the program (argv[0])
 * @env: Environment variables
 */
void	execute_command(char *command, char *program_name, char **env)
{
	pid_t	pid;
	char	**args;
	int	status;

	args = parse_command(command);
	if (!args)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_array(args);
		return;
	}
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			print_error(program_name, args[0]);
			free_array(args);
			_exit(1);
		}
	}
	else
	{
		wait(&status);
		free_array(args);
	}
}
