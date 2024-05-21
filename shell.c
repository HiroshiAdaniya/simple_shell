#include "shell.h"
/**
 * main - a simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int __attribute__((unused))argc, char *argv[])
{
	ssize_t i, child = 0;
	size_t len = 0;
	char delim[] = " \n";
	char **cmd, *getcmd = NULL;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		return (0);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#: ", 3);
		i = getline(&getcmd, &len, stdin);
		if (i == EOF)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		i = 0;
		cmd[i] = strtok(getcmd, delim);
		for (i = 1; cmd[i] != NULL; i++)
			cmd[i] = strtok(NULL, delim);

		child = fork();
		if (child == -1)
			break;
		if (child == 0 && cmd[1] == NULL)
		{
			i = execve(cmd[0], cmd, environ);
			if (i == -1)
			{
				perror(argv[0]);
				break;
			}
		}
		else
		{
			if (cmd[1] != NULL)
				perror(argv[0]);
			wait(NULL);
		}
	}
	free_mem(cmd, getcmd);
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

