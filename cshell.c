#include "shell.h"
/**
 * main - a simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on success
 */
int main(__attribute__((unused))int argc, char *argv[])
{
	char *string = NULL;
	char **command = malloc(sizeof(char *) * 2);
	ssize_t len = 0;
	size_t i = 0;
	pid_t pid = 0;

	if (command == NULL)
		return (0);
	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "cshell: ", 8);
			fflush(stdout);
		}
		len = getline(&string, &i, stdin);
		if (len == EOF || len == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		command[0] = strtok(string, "\n");
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			break;
		}
		else if (pid == 0)
		{
			command[1] = NULL;
			execve(string, command, environ);
				perror(argv[0]);
			break;
		}
		else
			wait(NULL);
	}
	free_mem(command, string);
	return (0);
}
/**
 * free_mem - frees memory
 * @command: an array of pointers to strings
 * @string: pointer to a string
 */
void free_mem(char **command, char *string)
{
	free(command);
	free(string);
}
