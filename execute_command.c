#include "shell.h"
/**
 * execute_command - executes a command
 * @program: a string containing the name of the program
 * @terminal: A structure holding the data received from the terminal
 */
void execute_command(char *program, string *terminal)
{
	char *path = NULL;

	path = getenv("PATH");
	if (path != NULL)
	{
		terminal->len = path_search(path, terminal);
		if (terminal->len != -1)
			forking(program, terminal);
	}
	else
		perror("$PATH");
	free_terminal_memory(&terminal);
}
/**
 * path_search - searches PATH directories for executables
 * @path: a pointer to a path
 * @terminal: a structure
 * Return: 0 on success, else -1
 */
ssize_t path_search(char *path, string *terminal)
{
	char *direc = NULL;
	char *real_path = NULL;
	char *fullpath = NULL;
	int len = 0;

	real_path = realpath(terminal->array[0], real_path);
	if (real_path != NULL && access(real_path, X_OK) == 0)
	{
		free(real_path);
		return (0);
	}
	else if (real_path != NULL && access(real_path, X_OK) == -1)
	{
		free(real_path);
		return (-1);
	}
	else
	{
		direc = strtok(path, ":");
		len = strlen(direc) + 2 + strlen(terminal->array[0]);
		fullpath = malloc(sizeof(char) * len + 1);
		if (fullpath != NULL)
			snprintf(fullpath, len, "%s/%s", direc, terminal->array[0]);
		else
			perror("malloc");
		if (fullpath != NULL && access(fullpath, X_OK) == 0)
		{
			free(fullpath);
			return (0);
		}
		else
		{
			while ((direc = strtok(NULL, ":")) != NULL)
			{
				len = strlen(direc) + 2 + strlen(terminal->array[0]);
				fullpath = realloc(fullpath, sizeof(char) * len + 1);
				if (fullpath != NULL)
					snprintf(fullpath, len, "%s/%s", direc, terminal->array[0]);
				else
					perror("malloc");
				if (fullpath != NULL && access(fullpath, X_OK) == 0)
				{
					free(fullpath);
					return (0);
				}
			}
		}
	}
	free(fullpath);
	return (-1);
}
/**
 * forking - forks the current calling process
 * @program: the name of the program
 * @terminal: a structure
 * Return: Nothing / void
 */
void forking(char *program, string *terminal)
{
	pid_t child = 0;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		free_terminal_memory(&terminal);
	}
	if (child == 0)
	{
		execve(terminal->array[0], terminal->array, environ);
		perror(program);
		free_terminal_memory(&terminal);
		exit(0);
	}
	else
		wait(NULL);
}
