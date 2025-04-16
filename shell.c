#include "shell.h"

extern char **environ;

/**
 * print_env - Prints the current environment
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

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
	char *full_path = find_command(argv[0]);

	if (!full_path)
	{
		perror("./hsh");
		free(argv);
		exit(EXIT_FAILURE);
	}

	execve(full_path, argv, environ);
	perror("./hsh");
	free(full_path);
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

/**
 * find_command - Resolves the full path of a command
 * @cmd: The command (e.g., "ls")
 *
 * Return: Full path string (malloc'd) if found, or NULL
 */
char *find_command(char *cmd)
{
	char *path = NULL, *path_copy = NULL, *dir = NULL;
	char *full_path = NULL;
	int len;

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd)); /* Already a valid path */

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
