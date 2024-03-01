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
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#: ", 4);
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
 * _execute - executes a command
 * @cmd: pointer to array of pointers
 * @getcmd: pointer to a string
 * @argv: argument vector
 * Return: nothing / void
 */
void _execute(char **cmd, char **argv, char *getcmd)
{
	ssize_t i = 0;

	i = execve(cmd[0], cmd, environ);
	if (i == -1)
	{
		cmderror(argv, cmd);
		free_mem(cmd, getcmd);
	}
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
