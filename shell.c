#include "shell.h"

/**
 * execute_command - Forks and executes a command with arguments
 * @line: The input command line
 */
int execute_command(char *line)
{
	pid_t pid;
	int status = 0;
	char **argv = NULL;
	char *full_path = NULL;

	if (line == NULL || line[0] == '\0')
		return (0);

	argv = tokenize(line);
	if (argv == NULL)
		return (0);

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(argv);
		return (1);
	}

	if (pid == 0)
	{
		full_path = find_command(argv[0]);
		if (!full_path)
		{
			dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", argv[0]);
			free(argv);
			exit(127);
		}

		if (execve(full_path, argv, environ) == -1)
		{
			perror("./hsh");
			free(argv);
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(argv);
	free(full_path);
	return (WEXITSTATUS(status));
}
