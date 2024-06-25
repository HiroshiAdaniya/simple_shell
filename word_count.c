#include "shell.h"
/**
 * word_count - count the amount of words in a string
 * @words: an int representing the number of words in s
 * @s: a pointer to a null-terminated string, a string the user inserted
 * Return: an int, else 0
 */
int word_count(int words, char *s)
{
	if (s == NULL)
		return  (0);

	if (strtok(s, " "))
		words++;
	while (strtok(NULL, " \n"))
		words++;

	return (words);
}
