#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read line from stdin */
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0); /* Exit on Ctrl+D */
		}
		/* Remove newline character */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Handle built-in exit */
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		if (strcmp(line, "env") == 0)
		{
			print_env();
			continue;
		}
		if (is_whitespace(line))
			continue;


	execute_command(line);

	}

	free(line);
	return (0);
}
