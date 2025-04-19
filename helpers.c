#include "shell.h"

/**
 * tokenize - Splits a string into an array of tokens
 * @line: The input line from user
 *
 * Return: Array of strings (tokens), or NULL
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
 * find_command - Resolves full path of a command using PATH
 * @cmd: The command to resolve
 *
 * Return: Full path if found (malloc'd), else NULL
 */
char *find_command(char *cmd)
{
	char *path = NULL, *path_copy = NULL, *dir = NULL;
	char *full_path = NULL;
	int len, i = 0;

	/* If command is an absolute or relative path, check directly */
	if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 || strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}

	/* Manually retrieve PATH from environment */
	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
		i++;
	}

	/* No PATH or it's empty */
	if (!path || *path == '\0')
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

/**
 * print_env - Prints the current environment variables
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
 * is_whitespace - Checks if a string is only spaces/tabs
 * @str: The input string
 * Return: 1 if only whitespace or empty, 0 otherwise
 */
int is_whitespace(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/**
 * trim_spaces - Removes leading and trailing spaces/tabs
 * @str: The input string to trim
 * Return: Pointer to the trimmed string (same buffer)
 */
char *trim_spaces(char *str)
{
	char *start = str;
	char *end;

	/* Skip leading spaces */
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == 0)
	{
		*str = '\0';
		return str;
	}

	/* Move trimmed content to the beginning */
	if (start != str)
		memmove(str, start, strlen(start) + 1);

	/* Trim trailing spaces */
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	end[1] = '\0';
	return str;
}
