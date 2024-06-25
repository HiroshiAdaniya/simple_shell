#include "shell.h"
/**
 * free_terminal_memory - frees memory in a structure
 * @terminal: the address of the termial pointer
 * Return: Nothing / void
 */
void free_terminal_memory(string **terminal)
{
	free((*terminal)->str);
	free((*terminal)->array);
	free(*terminal);
}
