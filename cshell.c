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
	char **command = NULL;
	ssize_t len = 0;
	size_t i = 0;
	pid_t pid = 0;

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
		if (string[i - 1] == '\n')
			string[i - 1] = '\0';
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			break;
		}
		else if (pid == 0)
		{
			*command[] = {string, NULL};
			execve(string, command, environ);
			perror(argv[0]);
			break;
		}
		else
			wait(NULL);
	}
	free(string);
	return (0);
}
