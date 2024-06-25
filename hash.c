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
			if (terminal != NULL)
				execute_command(argv[0], terminal);
		}
		else
		{
			terminal = read_line(false);
			if (terminal != NULL)
				execute_command(argv[0], terminal);
		}
	}

	return (0);
}
