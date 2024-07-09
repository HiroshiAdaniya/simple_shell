#include "shell.h"
/**
 * execute_command - executes a command
 * @program: a string containing the name of the program
 * @terminal: A structure holding the data received from the terminal
 */
void execute_command(char *program, string *terminal)
{
	char *path = NULL;

	terminal->len = 0;
	path = getenv("PATH");
	if (path != NULL)
		terminal->len = path_search(path, terminal);

	if (terminal->len != -1)
		forking(program, terminal);
	free_terminal_memory(&terminal);
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
/**
 * path_copy - copies a sting to another string
 * @path: the source string
 * Return: a pointer to a string, else NULL
 */
char *path_copy(char *path)
{
	int len = 0;
	char *string = NULL;

	len = strlen(path) + 1;
	if (len != 0)
	{
		string = malloc(sizeof(char) * len);
		if (string == NULL)
			return (NULL);
		memmove(string, path, len);
	}

	return (string);

}
/**
 * check_access - checks if the executable exists
 * @terminal: a structure
 * @direc: a pointer to hold string
 * @command: a pointer
 * Return: 0 on success, else -1
 */
ssize_t check_access(string *terminal, char *direc, char *command)
{
	terminal->len = -1;
	direc = strtok(terminal->path_copy, ":");
	terminal->len = strlen(direc) + strlen(terminal->array[0]) + 2;
	command = malloc(sizeof(char) * terminal->len);
	if (command == NULL)
	{
		perror("malloc");
		return (-1);
	}
	else
		snprintf(command, terminal->len, "%s/%s", direc, terminal->array[0]);
	if (command != NULL && access(command, F_OK | X_OK) == 0)
	{
		memmove(terminal->array[0], command, terminal->len);
		terminal->len = 0;
	}
	else
	{
		while ((direc = strtok(NULL, ":")) != NULL)
		{
			terminal->len = strlen(direc) + strlen(terminal->array[0]) + 2;
			command = realloc(command, sizeof(char) * terminal->len);
			if (command == NULL)
			{
				perror("malloc");
				terminal->len = -1;
				break;
			}
			else
				snprintf(command, terminal->len, "%s/%s", direc, terminal->array[0]);
			if (command != NULL && access(command, F_OK | X_OK) == 0)
			{
				memmove(terminal->array[0], command, terminal->len);
				terminal->len = 0;
				break;
			}
		}
	}
	free(command);
	return (terminal->len);
}

/**
 * path_search - searches PATH directories for executables
 * @path: a pointer to a path
 * @terminal: a structure
 * Return: 0 on success, else -1
 */
ssize_t path_search(char *path, string *terminal)
{
	ssize_t flag = -1;
	int len = 0;
	char *command = NULL;
	char *direc = NULL;

	len = realpath_check(terminal->array[0]);
	if (len == 0)
		return (0);
	else if (len == 1)
	{
		terminal->path_copy = path_copy(path);
		if (terminal->path_copy != NULL)
			flag = check_access(terminal, direc, command);

	}
	free(terminal->path_copy);
	return (flag);
}
