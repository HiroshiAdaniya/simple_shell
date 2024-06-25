#include "shell.h"
/**
 * initialize_struct - initializes all variable in a struct to either NULL or 0
 * to pass valgrind alerts
 * @terminal: A pointer to a struct
 * Return: Nothing / void
 */
void initialize_struct(string **terminal)
{
	(*terminal)->str = NULL;
	(*terminal)->array = NULL;
	(*terminal)->len = 0;
	(*terminal)->n = 0;
	(*terminal)->words = 0;
}
