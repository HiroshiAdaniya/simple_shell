#include "shell.h"
/**
 * main - a simple shell program
 * Return: 0 on success
 */
int main(void)
{
	ssize_t child, i = 0;
	size_t len = 0;
	char delim[] = " \n", **cmd, *str, *getcmd = NULL;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
	{
		free(cmd);
		return (0);
	}
	while (1 && i != EOF)
	{
		write(STDOUT_FILENO, "($): ", 6);
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(getcmd);
			return (0);
		}
		cmd[0] = strtok(getcmd, delim);
		str = strtok(NULL, delim);
		if (str != NULL)
		{
			cmd[0] = "null";
			cmd[1] = NULL;
		}
		child = fork();
		if (child == -1)
			return (0);
		if (child == 0)
		{
			i = execve(cmd[0], cmd, environ);
			if (i == -1)
				return (0);
		}
		else
			wait(NULL);
	}
	free(cmd);
	return (0);
}
