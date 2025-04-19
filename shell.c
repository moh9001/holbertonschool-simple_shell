#include "shell.h"

/**
 * execute_command - Forks and executes a command with arguments
 * @line: The input command line
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char **argv = NULL;
	char *full_path = NULL;

	if (line == NULL || line[0] == '\0')
		return;

	argv = tokenize(line);
	if (argv == NULL)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(argv);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Child process */
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
		/* Parent process */
		waitpid(pid, &status, 0);
	}

	free(argv);
	free(full_path);
}
