#include "shell.h"
/**
 * read_line - reads an entire line from stdin
 * Return: a pointer to a string, else NULL
 */
char *read_line(void)
{
	char *str = NULL;
	ssize_t length = 0;
	size_t n = 0;

	length = getline(&str, &n, stdin);

	if (length == EOF)
	{
		write(STDIN_FILENO, "\n", 1);
		free(str);
		return (NULL);
	}
	return (str);
}
