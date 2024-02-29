#include "shell.h"
void free_mem(char **, char *);
/**
 * main - a simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * @envp: environment pointer
 * Return: 0 on success
 */
int main(void)
{
	ssize_t child, i = 0;
	size_t len = 0;
	char delim[] = " \n", **cmd, *getcmd = NULL;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
	{
		free(cmd);
		return (0);
	}
	while (1 && child != EOF)
	{
		child = getline(&getcmd, &len, stdin);
		if (child == -1)
		{
			free_mem(cmd, getcmd);
			return (0);
		}
		cmd[i] = strtok(getcmd, delim);
		child = fork();
		if (child == -1)
			return (0);
		if (child == 0)
		{
			i = execve(cmd[0], cmd, envp);
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
 * free_mem - frees memory
 * @s: pointer to a pointer of char
 * @z: a pointer to a string
 * Return: NULL;
 */
void free_mem(char **s, char *z)
{
	free(s);
	free(z);
}
