#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * execute_command - Forks and executes a command
 * @line: The raw command line input from the user
 *
 * Return: Exit status of the executed command
 */
int execute_command(char *line)
{
	pid_t pid;
	int status = 0;
	char **argv = NULL;
	char *full_path = NULL;

	/* Ignore empty input */
	if (line == NULL || line[0] == '\0')
		return (0);

	/* Tokenize the input line into command + args */
	argv = tokenize(line);
	if (argv == NULL)
		return (0);

	/* Find the full path of the command (or return NULL if not found) */
	full_path = find_command(argv[0]);
	if (!full_path)
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", argv[0]);
		free(argv);
		return (127); /* Command not found */
	}

	/* Fork a child process to execute */
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(argv);
		free(full_path);
		return (1);
	}

	/* Child process */
	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror("./hsh");
			free(argv);
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	/* Parent process */
	else
	{
		waitpid(pid, &status, 0);
	}

	/* Cleanup */
	free(argv);
	free(full_path);

	return (WEXITSTATUS(status));
}
