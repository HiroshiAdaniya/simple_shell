#include "shell.h"
void free_mem(char **, char *);
/**
 * main - A simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: Always 0 (Successful)
 */
int main(int __attribute__((unused))argc, char *argv[])
{
	char *string, **command = NULL;
	ssize_t len, child = 0;
	size_t i = 0;

	command = malloc(sizeof(char *) * 2);
	if (command == NULL)
	{
		free(command);
		return (0);
	}
	while (1 && child != EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#: ", 3);
		len = getline(&string, &i, stdin);
		if (len == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			free_mem(command, string);
		}
		command[0] = strtok(string, "\n");
		command[1] = NULL;
		child = fork();
		if (child == -1)
			free_mem(command, string);
		if (child == 0)
		{
			child = execve(command[0], command, environ);
				if (child == -1)
					perror(argv[0]);
		}
		else
			wait(NULL);
	}
	return (0);
}
void free_mem(char **command, char *string)
{
	free(command);
	free(string);
	exit(EXIT_FAILURE);
}
