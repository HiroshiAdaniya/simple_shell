#ifndef SHELL_H
#define SHELL_H

/**
 * Global variables
 */

extern char **environ;

/**
 * Libraries
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>

/**
 * s - structure
 * @str: a pointer to a string
 * @array: NULL terminated array
 * @len: length of str
 * @n: number of bytes read
 * Description: points to the next node
 */

typedef struct string string;
struct string
{
	char *str;
	char **array;
	ssize_t len;
	size_t n;
	int words;
};


/**
 * Function prototypes
 */

void forking(char *, string *);

ssize_t locate_file(char *, string **);
ssize_t search_in_path(char *, string **);
void get_line(string **, int);
char **command_array(string *);
void execute_command(char *, string *);
void free_terminal_memory(string **);
void initialize_struct(string **terminal);
string *read_line(int);
void prompt(void);
void print(char *);
int word_count(int, char *);
int count_word(char *);
char **create_array(char *, int, ssize_t);

#endif
