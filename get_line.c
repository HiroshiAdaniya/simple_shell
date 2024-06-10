#include "shell.h"
/**
 * get_line - reads an entire line from stdin and removes newline char
 * Return: a pointer to a string, else NULL
 */
char *get_line(void)
{
	char *cmd = NULL;
	ssize_t bytes_read = 0;
	size_t size = 0;

	bytes_read = getline(&cmd, &size, stdin);

	if (bytes_read == EOF)
	{
		write(STDIN_FILENO, "\n", 1);
		free(cmd);
		return (NULL);
	}
	else if (bytes_read == -1)
	{
		perror("getline");
		free(cmd);
		return (NULL);
	}

	/* removes newline character */
	cmd[strcspn(cmd, "\n")] = '\0';

	return (cmd);
}
