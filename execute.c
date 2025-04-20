#include "shell.h"

/**
 * fork_and_exec - Forks and executes a command
 * @args: Command arguments
 * @full_path: Full path to command
 * @program_name: Program name
 * @env: Environment variables
 */
void fork_and_exec(char **args, char *full_path, char *program_name,
		char **env)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free_array(args);
		return;
	}
	if (pid == 0)
	{
		if (execve(full_path, args, env) == -1)
		{
			print_error(program_name, args[0]);
			free(full_path);
			free_array(args);
			_exit(1);
		}
	}
	else
	{
		wait(&status);
		free(full_path);
		free_array(args);
	}
}

/**
 * execute_command - Executes a command
 * @command: Command to execute
 * @program_name: Name of the program (argv[0])
 * @env: Environment variables
 */
void	execute_command(char *command, char *program_name, char **env)
{
	char	**args;
	char	*full_path;

	args = parse_command(command);
	if (!args)
		return;
	if (handle_builtins(args, program_name, env))
		return;
	full_path = find_command(args[0], env);
	if (!full_path)
	{
		print_error(program_name, args[0]);
		free_array(args);
		return;
	}
	fork_and_exec(args, full_path, program_name, env);
}
