#include "shell.h"
/**
 * search_in_path
 * @path: a pointer to a string
 * @terminal: a structure to a terminal
 * Return: 0 on success, else -1
 */
ssize_t search_in_path(char *path, string **terminal)
{
	char *path_dir = NULL;
	char *tmp_path = NULL;
	int length = 0;
	ssize_t found = -1;

	/* copies the variable path to another variable*/
	length = strlen(path);
	tmp_path = malloc(sizeof(char) * length + 1);
	if (tmp_path == NULL)
		return (-1);
	strcpy(tmp_path, path);

	/* breaks string into stokens*/
	path_dir = strtok(tmp_path, ":");
	found = locate_file(path_dir, terminal);
	if (found == -1)
	{
		while ((path_dir = strtok(NULL, ":")) != NULL)
		{
			found = locate_file(path_dir, terminal);	
			if (found == 0)
				break;
		}
	}

	free(tmp_path);
	return (found);
}
