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
		prompt();
		i = getline(&getcmd, &len, stdin);
		if (i == -1)
			free_mem(cmd, getcmd);
		cmd[0] = strtok(getcmd, delim);
		cmd[1] = NULL;
		child = fork();
		if (child == -1 || cmd[0] == NULL)
			free_mem(cmd, getcmd);
		if (child == 0)
			_execute(cmd, argv, getcmd);
		else
			wait(NULL);
	}
	return (0);
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
/**
 * prompt - displays a prompt
 * Return: nothing / void
 */
void prompt(void)
{
	write(STDOUT_FILENO, "#: ", 3);
}
/**
 * _execute - executes a program
 * @cmd: pointer to a pointer of strings
 * @argv: argument vector
 * @getcmd: a pointer to a string
 * Return: nothing / void
 */
void _execute(char **cmd, char **argv, char *getcmd)
{
	ssize_t j = 0;

	j = execve(cmd[0], cmd, environ);
	if (j == -1)
	{
		cmderror(argv, cmd);
		free_mem(cmd, getcmd);
	}
}
/**
 * free_mem - frees memory
 * @s: pointer to a pointer of char
 * @z: a pointer to a string
 * Return: void
 */
void free_mem(char **s, char *z)
{
	free(s);
	free(z);
	exit(0);
}
