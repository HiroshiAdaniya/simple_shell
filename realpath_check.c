#include "shell.h"
/**
 * realpath_check - checks a full path command
 * @command: a full path command
 * Return: 0 on success, else -1 on failure, else 1;
 */
ssize_t realpath_check(char *command)
{
	char *real_path = NULL;

	real_path = realpath(command, real_path);
	if (real_path != NULL && access(real_path, X_OK) == 0)
	{
		free(real_path);
		return (0);
	}
	else if (real_path != NULL && access(real_path, X_OK) == -1)
	{
		free(real_path);
		return (-1);
	}

	return (1);
}
