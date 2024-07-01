#include "shell.h"
/**
 * locate_file - searches a directory for a file
 * @path_dir: a string containing a directory in a path
 * @terminal: a pointer to a structure
 * Return: 0 on success, else -1 on failure
 */
ssize_t locate_file(char *path_dir, string **terminal)
{
	DIR *directory = NULL;
	char *path = NULL;
	int found = -1;
	struct dirent *dir_file = NULL;

	if (access(path_dir, F_OK | X_OK | R_OK) == 0)
	{
		directory = opendir(path_dir);
		if (directory == NULL)
			return (-1);
		/* realpath is used to handle a full path the user enters
		 * e.g /bin/ls OR /bin/pwd
		 * it does not handle single commands such as "ls" or "pwd"
		 */
		if ((path = realpath((*terminal)->array[0], NULL)) != NULL)
		{
			free(path);
			found = 0;
		}
		else
		{
			while ((dir_file = readdir(directory)) != NULL)
			{
				if (strcmp((*terminal)->array[0], dir_file->d_name) == 0)
				{
					/*free((*terminal)->array);
					(*terminal)->array = command_array(*terminal);
					(*terminal)->array[0] = concat_string(path_dir, dir_file->d_name);*/ /*check if lstat or stat has the files location */
					found = 0;
					break;

				}
			}
		}
	}

	closedir(directory);
	return (found);
}
