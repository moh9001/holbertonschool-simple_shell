#include "shell.h"

/**
 * check_absolute_path - Checks if command is an absolute/relative path
 * @command: Command to check
 * Return: Full path if executable, NULL otherwise
 */
char	*check_absolute_path(char *command)
{
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(command));
	}
	return (NULL);
}

/**
 * search_path - Searches PATH for command
 * @command: Command to find
 * @env: Environment variables
 * Return: Full path to command, or NULL if not found
 */
char	*search_path(char *command, char **env)
{
	char	*path = NULL;
	char	*path_copy;
	char	*dir;
	char	*full_path;
	int	i;
	struct stat st;

	for (i = 0; env[i]; i++)
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
	if (!path)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
 * find_command - Finds a command in PATH
 * @command: Command to find
 * @env: Environment variables
 * Return: Full path to command, or NULL if not found
 */
char	*find_command(char *command, char **env)
{
	char	*full_path;

	full_path = check_absolute_path(command);
	if (full_path)
		return (full_path);
	return (search_path(command, env));
}
