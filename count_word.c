#include "shell.h"
/**
 * count_word - counts the amount of words in a string depending on delimiter
 * @str: a null-terminated string
 * Return: an int, else 0
 */
int count_word(char *str)
{
	int count = 0;

	if (str == NULL)
		return (0);

	if (strtok(str, "\n"))
		count++;
	while (strtok(NULL, "\n"))
		count++;

	return (count);
}
