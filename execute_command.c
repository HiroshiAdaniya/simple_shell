#include "shell.h"
/**
 * execute_command - executes a command
 * @string: a null-terminated string
 * @argv: a null-terminated string, the program name
 * Return: Nothing / void
 */
void execute_command(char *string, char *argv)
{
	char **array = NULL;
	pid_t pid = 0;
	int status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		array = malloc(sizeof(char *) * 2);
		if (array == NULL)
		{
			perror("malloc");
			return;
		}
		array[0] = string;
		array[1] = NULL;
		execve(array[0], array, environ);
			perror(argv);
		exit(0);
	}
	else
		wait(&status);
}
