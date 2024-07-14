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
 * struct string - a user defined data type, a structure
 * @str: a pointer to a string
 * @path_array: an array of stings, NULL terminated / path directories
 * @array: an array of strings, NULL terminated / commands
 * @len: length of str
 * @n: number of bytes read
 * @words: an int representing the number of words in str
 *
 * Description: a data structure that will be used to run the simple shell
 */

typedef struct string string;
struct string
{
	char *str;
	char *path_copy;
	char **array;
	ssize_t len;
	size_t n;
	int words;
};


/**
 * Function prototypes
 */

void print_env(string *);
void exit_program(string *, int);
int not_found(char *, char *, int, string *);
ssize_t path_search(char *path, string *);
ssize_t realpath_check(char *);
char *path_copy(char *);
ssize_t check_access(string *, char *, char *);
void forking(char *, string *);
void get_line(string **, int);
char **command_array(string *);
int execute_command(char *, string *, int);
void free_terminal_memory(string **);
void initialize_struct(string **terminal);
string *read_line(int);
void prompt(void);
void print(char *);
int word_count(int, char *);
int count_word(char *);
char **create_array(char *, int, ssize_t);

#endif
