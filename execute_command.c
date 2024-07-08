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
		/*terminal->len = search_in_path(path, &terminal);
		if (terminal->len != -1)*/
			forking(program, terminal);
	}
	else
		perror("$PATH");
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
