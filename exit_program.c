#include "shell.h"
/**
 * exit_program - if the user enters "exit", program terminates
 * @terminal: a structure
 * @flag: to indicate if the first command is exit
 * Return: nothing / void
 */
void exit_program(string *terminal, int flag)
{
	char *str = NULL;
	size_t n = 0;

	if (strcmp(terminal->array[0], "exit") == 0 &&
	terminal->array[1] == NULL && flag == true)
	{
		free_terminal_memory(&terminal);
		exit(0);
	}
	else if (realpath_check(terminal->array[0]) == 0 &&
	terminal->array[1][0] == '/' &&
	flag == false && getline(&str, &n, stdin) != -1)
	{
		if (strcmp(str, "exit\n") == 0)
		{
			free(str);
			free_terminal_memory(&terminal);
			exit(2);
		}
	}

	free(str);
}
