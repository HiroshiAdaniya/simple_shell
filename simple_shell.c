#include "main.h"
/**
 * main - prints 4 environment variables, PID and PPID
 * Return: 0 on success
 */
int main(void)
{
	int i, j, len = 0;
	char *list[] = {"USER", "SHELL", "BROWSER", "PATH", NULL};

	for (i = 0; i < 50;  i++)
		printf("=");
	printf("\n\n");
	for (i = 0; list[i] != NULL; i++)
	{
		len = strlen(list[i]);
		for (j = 0; environ[j] != NULL; j++)
		{
			if (strncmp(list[i], environ[j], len) == 0)
			{
				printf("%s: %s\n", list[i], environ[j]);
				break;
			}
		}
	}
	putchar('\n');
	for (i = 0; i < 50; i++)
		printf("=");
	printf("\n\nPID of current proccess:%d\n", getpid());
	printf("PID of current parent process: %d\n\n", getppid());
	for (i = 0; i < 50; i++)
		printf("=");
	putchar('\n');
	i = simple_shell();
	if (i == -1)
	{
		printf("Could not run shell\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
/**
 * simple_shell - a simple shell program
 * Return: 0 on success
 */
int simple_shell(void)
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
