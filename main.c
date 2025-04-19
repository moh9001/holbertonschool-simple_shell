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
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		trim_spaces(line);

		if (is_whitespace(line))
			continue;

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

		ret = execute_command(line);

		if (!isatty(STDIN_FILENO))
		{
			free(line);
			exit(ret);
		}
	}

	free(line);
	return (0);
}
