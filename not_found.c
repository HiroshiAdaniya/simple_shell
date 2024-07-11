#include "shell.h"
/**
 * not_found - prints an error message to stderr if command not found
 * @program: name of the program
 * @command: name of the commmand
 * @flag: determining interactive or non-interactive mode
 * @terminal: a structure
 * Return: an int, error code
 */
int not_found(char *program, char *command, int flag, string *terminal)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program, command);
	if (flag == false)
	{
		free_terminal_memory(&terminal);
		exit(127);
	}
	else
		flag = 127;
	return (flag);
}
