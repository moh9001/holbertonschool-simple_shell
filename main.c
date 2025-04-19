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
	int ret;

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

		/* Handle built-in env */
		if (strcmp(line, "env") == 0)
		{
			print_env();
			continue;
		}

		/* Skip whitespace-only input */
		if (is_whitespace(line))
			continue;

		/* Execute command and get return code */
		ret = execute_command(line);

		/* If in non-interactive mode (e.g., pipe/script), exit with ret code */
		if (!isatty(STDIN_FILENO))
		{
			free(line);
			exit(ret);
		}
	}

	free(line);
	return (0);
}
