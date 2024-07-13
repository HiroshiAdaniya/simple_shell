#include "shell.h"
/**
 * exit_program - if the user enters "exit", program terminates
 * @terminal: a structure
 * Return: nothing / void
 */
void exit_program(string *terminal)
{
	if (strcmp(terminal->array[0], "exit") == 0 && terminal->array[1] == NULL)
	{
		free_terminal_memory(&terminal);
		exit(0);
	}
	else if (terminal->array[0][0] == '/' && terminal->array[1][0] == '/')
	{
		free_terminal_memory(&terminal);
		exit(2);
	}
}
