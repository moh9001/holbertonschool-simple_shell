#include "shell.h"

/**
 * free_array - Frees an array of strings
 * @array: Array to free
 */
void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * has_non_whitespace - Checks if a string contains non-whitespace characters
 * @str: String to check
 * Return: 1 if non-whitespace character is found, 0 otherwise
 */
int	has_non_whitespace(char *str)
{
	int	i;

	if (!str)
		return (0);
	for (i = 0; str[i]; i++)
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
	return (0);
}
