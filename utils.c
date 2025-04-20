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
