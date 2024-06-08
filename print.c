#include "shell.h"
/**
 * print - prints a string to stdout
 * @str: a null-terminated string
 * Return: Nothing / void
 */
void print(char *str)
{
	if (str == NULL)
		return;
	write(STDOUT_FILENO, str, strlen(str));
}
