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

/* env.c */
char **get_environ(info_t *info);
int _setenv(info_t *info, char *var, char *value);
int _unsetenv(info_t *info, char *var);

#endif /* SHELL_DEMO_H */
