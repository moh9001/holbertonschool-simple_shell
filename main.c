#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: 0 on success, 1 on failure
 */
int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	char	*program_name = argv[0];

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[0] != '\0')
			execute_command(line, program_name, env);
		free(line);
	}
	return (0);
}
