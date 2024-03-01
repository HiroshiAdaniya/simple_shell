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

int main(int, char **);
void free_mem(char **, char *);
void cmderror(char **, char **);
void prompt(void);
void _execute(char **cmd, char **argv, char *getcmd);
#endif
