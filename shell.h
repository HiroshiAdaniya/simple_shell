#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

void free_mem(char **, char *);
char *NoNewline(char *);
void Error(char **, char *, ssize_t);
#endif
