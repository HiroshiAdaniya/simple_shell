#include "shell.h"
/**
 * exit_program - if the user enters "exit", program terminates
 * @terminal: a structure
 * @flag: to indicate if the first command is exit
 * Return: nothing / void
 */
void exit_program(string *terminal, int flag)
{
	if (strcmp(terminal->array[0], "exit") == 0 &&
	terminal->array[1] == NULL && flag == true)
	{
		free_terminal_memory(&terminal);
		exit(0);
	}
	else if (flag != true)
	{
		free_terminal_memory(&terminal);
		exit(2);
	}
}
