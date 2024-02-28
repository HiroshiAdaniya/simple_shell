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
	while (1 && i != EOF)
	{
		printf("($): ");
		i = 0;
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
		{
			printf("terminated\n");
			exit(EXIT_FAILURE);
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
			return (-1);
		if (child == 0)
		{
			i = execve(cmd[0], cmd, environ);
			if (i == -1)
				perror("failed");
		}
		else
			wait(NULL);
	}
	free(cmd);
	return (0);
}
