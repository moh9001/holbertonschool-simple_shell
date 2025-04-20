#include "shell.h"

/**
 * fork_and_exec - Forks and executes a command
 * @args: Command arguments
 * @full_path: Full path to command
 * @program_name: Program name
 * @env: Environment variables
 * @status: Pointer to store exit status
 */
void	fork_and_exec(char **args, char *full_path, char *program_name
		, char **env, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		*status = 1;
		return;
	}
	if (pid == 0)
	{
		if (execve(full_path, args, env) == -1)
		{
			print_error(program_name, args[0]);
			free(full_path);
			_exit(127);
		}
	}
	else
	{
		wait(status);
		free(full_path);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
}

/**
 * execute_command - Executes a command
 * @command: Command to execute
 * @program_name: Name of the program (argv[0])
 * @env: Environment variables
 * @last_status: Last command's exit status
 * Return: Exit status of the command
 */
int	execute_command(char *command, char *program_name, char **env
		, int last_status)
{
	char	**args;
	char	*full_path;
	int	status;
	int	builtin_handled = 0;

	args = parse_command(command);
	if (!args)
		return (1);
	status = handle_builtins(args, program_name, env, last_status
			, &builtin_handled);
	if (builtin_handled)
	{
		free_array(args);
		return (status);
	}
	full_path = find_command(args[0], env);
	if (!full_path)
	{
		print_error(program_name, args[0]);
		free_array(args);
		return (127);
	}
	fork_and_exec(args, full_path, program_name, env, &status);
	free_array(args);
	return (status);
}
