#include "shell.h"

extern char **environ;

/**
 * execute_command - Forks and executes a command with arguments
 * @line: The input command line (e.g. "/bin/ls -l")
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char **argv = NULL;

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
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./hsh");
			free(argv);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process waits */
		waitpid(pid, &status, 0);
		free(argv);
	}
}

/**
 * tokenize - Splits a string into tokens
 * @line: The input line to tokenize
 *
 * Return: Array of strings (tokens), or NULL on failure
 */
char **tokenize(char *line)
{
	char *token = NULL, *copy = NULL;
	char **tokens = NULL;
	int i = 0, count = 0;

	if (line == NULL)
		return (NULL);

	copy = strdup(line);
	if (copy == NULL)
		return (NULL);

	token = strtok(copy, " \t\n");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(copy);

	tokens = malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;

	return (tokens);
}
