#include "main.h"
/**
 * main - a simple shell program
 * Return: 0 on success
 */
int main(void)
{
	ssize_t child, len;
	char *delim = " \n";
	char **cmd, *getcmd;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	while (1 && len != EOF)
	{
		printf("($): ");
		len = 0;
		len = getline(&getcmd, &len, stdin);
		if (len == -1)
		{
			printf("terminated\n");
			exit(EXIT_FAILURE);
		}
		cmd = realloc(cmd, sizeof(char *) * len);
		if (cmd == NULL)
			exit(EXIT_FAILURE);
		cmd[0] = strtok(getcmd, delim);
		cmd[1] = strtok(NULL, delim);
		if (cmd[1] != NULL)
			cmd[0] = "(null)";
		child = fork();
		if (child == -1)
			exit(EXIT_FAILURE);
		if (child == 0)
		{
			len = execve(cmd[0], cmd, environ);
			if (len == -1)
				perror("failed");
		}
		else
			wait(NULL);
	}
	return (0);
}
