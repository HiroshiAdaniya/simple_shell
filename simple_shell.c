#include "shell.h"
/**
 * main - entry point, Simple shell program
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 on Success
 */
int main(__attribute__((unused)) int argc, char *argv[], char *envp[])
{
	char *string = NULL;

	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt();
			string = get_line();
			if (string == NULL)
				break;
			execute_isatty(string, argv[0], envp);
		}
		else
		{
			string = get_line();
			if (string == NULL)
				break;
			execute(string, argv[0], envp);
		}
	}

	free(string);
	return (0);
}
