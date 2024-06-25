#include "shell.h"
/**
 * print - prints a string
 * @str: a null-terminated string
 * Return: nothig / void
 */
void print(char *str)
{
	size_t len = 0;

	if (str == NULL)
		return;
	len = strlen(str);
	write(STDOUT_FILENO, str, len);
}
