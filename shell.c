#include "shell.h"
void free_mem(char **, char *);
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
		write(STDOUT_FILENO, "&: ", 3);
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
		{
			free_mem(cmd, getcmd);
			putchar('\n');
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
			{
				free_mem(cmd, getcmd);
				return (0);
			}
		}
		else
			wait(NULL);
	}
	return (0);
}
/**
 * free_mem - frees memeory
 * @s: pointer to a pointer of char
 * @z: a pointer to a string
 * Return: NULL;
 */
void free_mem(char **s, char *z)
{
	free(s);
	free(z);
}
