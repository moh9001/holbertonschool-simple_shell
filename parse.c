#include "shell.h"

/**
 * count_args - Counts number of arguments in a line
 * @line: Input line
 * @arg_count: Pointer to store count
 */
void	count_args(char *line, int *arg_count)
{
	char	*temp;
	char	*token;

	*arg_count = 0;
	if (!line || !*line)
		return;
	temp = strdup(line);
	if (!temp)
		return;
	token = strtok(temp, " \t\n");
	while (token)
	{
		if (*token)
			(*arg_count)++;
		token = strtok(NULL, " \t\n");
	}
	free(temp);
}

/**
 * store_args - Stores arguments from line into array
 * @line: Input line
 * @args: Array to store arguments
 * @arg_count: Number of arguments
 */
void	store_args(char *line, char **args, int arg_count)
{
	char	*temp;
	char	*token;
	int	i = 0;

	if (!line || !*line)
		return;
	temp = strdup(line);
	if (!temp)
		return;
	token = strtok(temp, " \t\n");
	while (token && i < arg_count)
	{
		if (*token)
		{
			args[i] = strdup(token);
			if (!args[i])
			{
				while (i > 0)
					free(args[--i]);
				free(temp);
				return;
			}
			args[i][strcspn(args[i], "\n")] = '\0';
			i++;
		}
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	free(temp);
}

/**
 * parse_command - Parses a command line into an array of arguments
 * @line: Input line
 * Return: Array of arguments, or NULL on failure
 */
char	**parse_command(char *line)
{
	char	**args;
	int	arg_count;

	if (!line || !*line)
		return (NULL);
	count_args(line, &arg_count);
	if (arg_count == 0)
		return (NULL);
	args = malloc((arg_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	store_args(line, args, arg_count);
	return (args);
}
