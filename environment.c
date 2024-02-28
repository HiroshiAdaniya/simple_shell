#include "main.h"
/**
 * main - prints 4 environment variables, PID and PPID
 * Return: 0 on success
 */
int main(void)
{
	int i, j, len = 0;
	char *list[] = {"USER", "SHELL", "BROWSER", "PATH", NULL};

	for (i = 0; i < 50;  i++)
		printf("=");
	printf("\n\n");
	for (i = 0; list[i] != NULL; i++)
	{
		len = strlen(list[i]);
		for (j = 0; environ[j] != NULL; j++)
		{
			if (strncmp(list[i], environ[j], len) == 0)
			{
				printf("%s: %s\n", list[i], environ[j]);
				break;
			}
		}
	}
	putchar('\n');
	for (i = 0; i < 50; i++)
		printf("=");
	printf("\n\nPID of current proccess:%d\n", getpid());
	printf("PID of current parent process: %d\n\n", getppid());
	for (i = 0; i < 50; i++)
		printf("=");
	putchar('\n');

	return (0);
}
