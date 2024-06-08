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

/**
 * Function prototypes
 */

void prompt(void);
void print(char *);
int strlength(char *);
char *read_line(void);
void execute_command(char *, char *);

char **allocation(char *);
#endif
