#include "shell.h"
/**
 * command_array - creates an array of strings from str
 * @terminal: a user defined structure
 * Return: Nothing / void
 */
char **command_array(string *terminal)
{
	int i = 0;
	int j = 0;
	char *tmp;

	tmp = terminal->str;
	j = word_count(j, tmp);
	if (j != 0)
		terminal->array = malloc(sizeof(char *) * (j + 1));
	else
		return (NULL);

	terminal->array[i] = strtok(terminal->str, " ");
	i++;
	while ((terminal->array[i] = strtok(NULL, " ")) != NULL)
		i++;

	terminal->array[i] = NULL;

	return (terminal->array);
}
