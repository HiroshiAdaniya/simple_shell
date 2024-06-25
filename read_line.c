#include "shell.h"
/**
 * read_line - reads an entire line from stdin,
 * Finds the amount of words in str
 * Assigns an array of strings to an array
 * @flag: an integer representing a terminal or not
 * Return: a malloced structure, else NULL;
 */
string *read_line(int flag)
{
	string *terminal = NULL;

	terminal = malloc(sizeof(string));
	if (terminal == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	initialize_struct(&terminal);
	terminal->len = getline(&terminal->str, &terminal->n, stdin);
	if (terminal->len == EOF)
	{
		if (flag == true)
			write(STDOUT_FILENO, "\n", 1);
		free(terminal->str);
		free(terminal);
		exit(0);
	}
	terminal->len = strlen(terminal->str);
	if (terminal->str[terminal->len - 1] == 10)
		terminal->str[terminal->len - 1] = '\0';

	if (flag == true)
		terminal->words = count_word(terminal->str);
	else
	{
		terminal->array = command_array(terminal);
		if (terminal->array[0] == NULL)
		{
			free(terminal->str);
			free(terminal);
			return (NULL);
		}
	}
	if (terminal->words != 0 && terminal->len > 0 && /*new code*/ flag == true)
	{
		terminal->array = create_array(terminal->str, terminal->words,
		terminal->len);
		if (terminal->array == NULL)
		{
			free_terminal_memory(&terminal);
			return (NULL);
		}
	}

	return (terminal);
}
