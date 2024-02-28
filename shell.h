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

int main(void);
int simple_shell(void);
#endif
