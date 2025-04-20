#include "shell.h"

/**
 * parse_command - Parses a command line into an array of arguments
 * @line: Input line
 * Return: Array of arguments, or NULL on failure
 */
char	**parse_command(char *line)
{
	char	**args;
	char	*token;
	int	i = 0;
	int	arg_count = 0;

	char	*temp = strdup(line);
	if (!temp)
		return (NULL);
	token = strtok(temp, " \t");
	while (token)
	{
		arg_count++;
		token = strtok(NULL, " \t");
	}
	free(temp);

	args = malloc((arg_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);

	token = strtok(line, " \t");
	while (token && i < arg_count)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
	return (args);
}
