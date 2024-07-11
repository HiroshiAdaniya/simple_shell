#include "shell.h"
/**
 * free_terminal_memory - frees memory in a structure
 * @terminal: the address of the termial pointer
 * Return: Nothing / void
 */
void free_terminal_memory(string **terminal)
{
	free((*terminal)->str);
	if ((*terminal)->words == -1)
		free((*terminal)->array[0]);
	free((*terminal)->array);
	free(*terminal);
}
