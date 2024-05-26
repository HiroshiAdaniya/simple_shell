#include "shell.h"
/**
 * main - entry point, a simple shell program
 * @argc: argument counter, (unused)
 * @argv: argument vector
 * Return: 0 on Success
 */
int main(__attribute__((unused)) int argc, char *argv[])
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r = 0;
	char **cmd = NULL;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		return (-1);

	while (true)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, ":) ", 3);
		r = getline(&line, &n, stdin);
		fflush(stdin);
		if (r == EOF || r == -1)
			Error(cmd, line, r);
		cmd[0] = strtok(line, "\n");
		cmd[1] = NULL;
		r = fork();
		if (r == -1)
			return (-1);
		if (r == 0)
		{
			r = execve(cmd[0], cmd, environ);
			if (r == -1)
			perror(argv[0]);
			break;
		}
		else
			wait(NULL);
	}
	free_mem(cmd, line);
	return (0);
}
/**
 * Error - Error Handling of getline()
 * @cmd: pointer to an array of pointers
 * @line: a pointer to a string
 * @r: an int  indicating the error
 * Return: Nothing / void
 */
void Error(char *cmd[], char *line, ssize_t r)
{
	free_mem(cmd, line);
	exit(-1);
}
/**
 * NoNewline - removes the newline in the string
 * @line: a pointer to a string
 * Return: a string with no newline, else NULL
 */
char *NoNewline(char *line)
{
	int i = 0;

	while (line[i] != '\n')
	{
		i++;
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return (line);
		}
	}

	return (NULL);
}
/**
 * free_mem -  frees memory
 * @cmd: a pointer to array of pointers of strings
 * @line: a pointer to a string
 * Return: Nothing / void
 */
void free_mem(char *cmd[], char *line)
{
	free(cmd);
	free(line);
}
