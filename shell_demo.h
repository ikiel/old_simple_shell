#ifndef SHELL_DEMO_H
#define SHELL_DEMO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

/* BUILT-IN FUNCTIONS */
void change_directory(char **arg);

#endif /* SHELL_DEMO_H */
