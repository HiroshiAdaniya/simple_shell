#include "shell.h"
/**
 * execute_command - executes a command
 * @string: a null-terminated string
 * @argv: a null-terminated string, the program name
 * Return: Nothing / void
 */
void execute_command(char *string, char *argv, char **envp)
{
	char **array = NULL;
	pid_t pid = 0;
	int status = 0;
	int len = 0;

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
			free(array);
			free(string);
			return;
		}
		array[0] = strtok(string, " \n");
		len = strlen(array[0]);
		array[0][len] = '\0';
		array[1] = NULL;
		execve(array[0], array, envp);
		if (errno != EFAULT)
			perror(argv);
		free(array[0]);
		free(array[1]);
		free(array);
		exit(0);
	}
	else
		wait(&status);
	free(string);
}
