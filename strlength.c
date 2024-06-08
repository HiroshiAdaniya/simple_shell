#include "shell.h"
/**
 * strlength - finds the length of a string, excluding the '\0' char
 * @str: a null-terminated string
 * Return: length of a string, else 0
 */
int strlength(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (str[i] != '\n')
		i++;
	i++;

	return (i);
}
