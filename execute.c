#include "shell.h"
/**
 * execute - executes a command
 * @string: a null-terminated string
 * @argv: a null-terminated string, the program name
 * @envp: environment variable
 * Return: Nothing / void
 */
void execute(char *string, __attribute__((unused))char *argv, char **envp)
{
	char **array = NULL;
	pid_t pid = 0;
	int status = 0;
	/* int len = 0;*/

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(string);
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
		array[0] = strtok(string, " ");
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
