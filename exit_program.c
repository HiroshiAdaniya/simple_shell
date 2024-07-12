#include "shell.h"
/**
 * exit_function - if the user enters "exit", program terminates
 * @terminal: a structure
 * Return: nothing / void
 */
void exit_function(string *terminal)
{
	if (strcmp(terminal->array[0], "exit") == 0 && terminal->array[1] == NULL)
	{
		free_terminal_memory(&terminal);
		exit(0);
	}
	else if (strcmp(terminal->array[1], "exit") == 0)
	{
		exit(2);
	}
}
