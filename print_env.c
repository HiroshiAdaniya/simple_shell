#include "shell.h"
/**
 * print_env - prints the environment of the current process
 * @terminal: a user defined structure
 * Return: 1 on success, else 0
 */
int print_env(string *terminal)
{
	int i = 0;

	if (environ == NULL)
		terminal->words = -1;
	else if (strcmp(terminal->array[0], "env") == 0 && terminal->array[1] == NULL)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
	}
}
