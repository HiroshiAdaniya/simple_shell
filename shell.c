#include "shell.h"
/**
 * main - a simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	ssize_t child, i = 0;
	size_t len = 0;
	char delim[] = " \n", **cmd, *getcmd = NULL;

	if (argc < 1)
		return (0);
	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
	{
		free(cmd);
		return (0);
	}
	while (1 && i != EOF)
	{
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
		{
			free_mem(cmd, getcmd);
			return (0);
		}
		cmd[0] = strtok(getcmd, delim);
		cmd[1] = NULL;
		child = fork();
		if (child == -1)
			return (0);
		if (child == 0)
		{
			i = execve(cmd[0], cmd, environ);
			if (i == -1)
			{
				cmderror(argv, cmd);
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
/**
 * cmderror - prints error message if command not found
 * @argv: argvument vector
 * @cmd: command
 * Return: nothing / void
 */
void cmderror(char **argv, char **cmd)
{
	printf("%s: 1: %s: not found\n", argv[0], cmd[0]);
}
