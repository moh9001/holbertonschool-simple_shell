#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void	display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
	fflush(stdout);
}

/**
 * read_line - Reads a line from standard input
 * Return: Pointer to the line read, or NULL on EOF/error
 */
char	*read_line(void)
{
	char	*line = NULL;
	size_t	bufsize = 0;
	ssize_t	chars_read;

	chars_read = getline(&line, &bufsize, stdin);
	if (chars_read == -1)
	{
		free(line);
		return (NULL);
	}
	line[strcspn(line, "\n")] = '\0';
	return (line);
}
