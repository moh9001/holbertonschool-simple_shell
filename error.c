#include "shell.h"

/**
 * print_error - Prints an error message
 * @program_name: Name of the program
 * @command: Command that caused the error
 */
void	print_error(char *program_name, char *command)
{
	char	error_msg[256];
	int	len;

	len = sprintf(error_msg, "%s: 1: %s: not found\n", program_name, command);
	write(STDERR_FILENO, error_msg, len);
}
