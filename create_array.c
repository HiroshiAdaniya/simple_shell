#include "shell.h"
/**
 * create_array - creates an array of strings that is NULL terminated
 * @str: a null-terminated string
 * @words: an integer representing the number of words in str
 * @len: The length of str
 * Return: An array of strings, else NULL
 */
char **create_array(char *str, int words, ssize_t len)
{
	char **array = NULL;
	ssize_t i = 0;
	int j = 0;
	char last_character = '\0';

	array = malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		if (str[i] != '\0' && last_character == '\0')
		{
			array[j] = str + i;
			j++;
		}

		last_character = str[i];
	}

	array[j] = NULL;

	return (array);
}
