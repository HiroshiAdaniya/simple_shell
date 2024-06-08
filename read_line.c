#include "shell.h"
/**
 * read_line - reads an entire line from stdin
 * Return: a pointer to a string, else NULL
 */
char *read_line(void)
{
	char *str = NULL;
	size_t length = 0;
	ssize_t retValue = 0;
	int len = 0;

	retValue = getline(&str, &length, stdin);
	if (retValue == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(str);
		return (NULL);
	}
	else if (retValue == -1)
	{
		perror("Malloc");
		free(str);
		return (NULL);
	}

	len = strlength(str);
	str[len - 1] = '\0';

	return (str);
}
