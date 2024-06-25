#include "shell.h"
/**
 * command_array - creates an array of strings from str
 * @terminal: a user defined structure
 * Return: Nothing / void
 */
char **command_array(string *terminal)
{
	int i = 1;
	int j = 0;
	int flag = 0; /*new code*/
	/*char *tmp;

	tmp = terminal->str;
	j = word_count(j, tmp);
	if (j != 0)
		terminal->array = malloc(sizeof(char *) * (j + 1));
	else
		return (NULL);*/

	while (terminal->str[j] != '\0')
	{
		if (terminal->str[j] == ' ')
			i++;
		if (terminal->str[j] != ' ')
			flag++; /*new flag*/
		j++;
	}
	if (flag != 0)
	{
		terminal->array[0] = NULL;
		return (terminal->array);
	} /*new code*/
	terminal->array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	terminal->array[i] = strtok(terminal->str, " ");
	i++;
	while ((terminal->array[i] = strtok(NULL, " ")) != NULL)
		i++;
	terminal->array[i] = NULL;

	return (terminal->array);
}
