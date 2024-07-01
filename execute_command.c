#include "shell.h"
/**
 * execute_command - executes a command
 * @program: a string containing the name of the program
 * @terminal: A structure holding the data received from the terminal
 */
void execute_command(char *program, string *terminal)
{
	pid_t child = 0;
	/* new code starts here */
	char *path = NULL;

	if (strcmp(terminal->array[0], "exit") == 0)
	{
		free_terminal_memory(&terminal);
		exit(0);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		perror("$PATH");
		terminal->len = -1;
	}
	terminal->len = search_in_path(path, &terminal);

	if (terminal->len != -1)
	{
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

	free_terminal_memory(&terminal);
}
