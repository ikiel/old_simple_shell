#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

extern char **environ;

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* getline.c */
int readline(char *str, size_t len);
char *remove_newline(char *str);
void tokenize(char *str, char **args);

/* string_functions.c */
void _puts(char *str);
void prompt(char *str);
char *_strcpy(char *dest, char *src);
int _putchar(char c);
int _strlen(char *s);

#endif
