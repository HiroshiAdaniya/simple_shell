#include "shell.h"
/**
 * main - a simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int __attribute__((unused))argc, char *argv[])
{
	ssize_t child, i = 0;
	size_t len = 0;
	char delim[] = " ", **cmd, *getcmd = NULL;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
	{
		free(cmd);
		return (0);
	}
	while (1 && i != EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#: ", 3);
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			free_mem(cmd, getcmd);
		}
		cmd[0] = strtok(getcmd, delim);
		cmd[1] = NULL;
		child = fork();
		if (child == -1 || cmd[0] == NULL)
			free_mem(cmd, getcmd);
		if (child == 0)
		{
			i = execve(cmd[0], cmd, environ);
			if (i == -1)
			{
				perror(argv[0]);
				free_mem(cmd, getcmd);
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
	exit(0);
}
