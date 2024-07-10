#include "shell.h"
/**
 * main - entry point, simple_shell
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	string *terminal = NULL;

	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt();
			terminal = read_line(true);
			if (terminal != NULL && terminal->str[0] != '\0')
				execute_command(argv[0], terminal, true);
			else if (terminal != NULL && terminal->str[0] == '\0')
				free_terminal_memory(&terminal);
		}
		else
		{
			terminal = read_line(false);
			if (terminal != NULL && terminal->str[0] != '\0')
				execute_command(argv[0], terminal, false);
			else if (terminal != NULL && terminal->str[0] == '\0')
				free_terminal_memory(&terminal);
		}
	}

	return (0);
}
