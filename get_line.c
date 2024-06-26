#include "shell.h"
/**
 * get_line - receives an entire line from stdin
 * @terminal: a pointer to a structure
 * @flag: an int representing terminal input or not
 * Return: exits with 0 if function fails
 */
void get_line(string **terminal, int flag)
{
	(*terminal)->len = getline(&(*terminal)->str, &(*terminal)->n, stdin);
	if ((*terminal)->len == EOF)
	{
		if (flag == true)
			write(STDOUT_FILENO, "\n", 1);
		free((*terminal)->str);
		free((*terminal));
		exit(0);
	}
}
