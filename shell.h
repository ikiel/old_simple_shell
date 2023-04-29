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
#include <stdarg.h>

extern char **environ;

#define BUF_SIZE 1024
#define BUFFER_SIZE 4096
#define BUF_FLUSH -1


/* linkedlists.c */

/**
 * struct list_s - singly linked list node
 * @str: string data
 * @val: value string data
 * @len: length of the string data
 * @valLen: length of the value string data
 * @next: pointer to the next node in the list
 *
 * Description: This struct represents a node in a singly linked list
 * for the simple_shell project
*/

typedef struct list_s
{
	char *str;
	char *val;
	unsigned int len;
	unsigned int valLen;
	struct list_s *next;
} list_t;

size_t print_list(list_t *h);
size_t list_len(list_t *h);
list_t *add_node(list_t **head, char *str, char *val);
void free_list(list_t *head);
list_t *get_node(list_t *head, char *str);


/**
 * struct args - structure used to hold all shell variables needed
 * @argv: command line argument from main function
 * @buffer: input buffer
 * @args: array of arguments
 * @nextCommand: the next command to process
 * @argsCap: num of arguments the args array can hold
 * @lineCount: total line of input
 * @tokCount: num of tokens in a line input
 * @status: run command return status
 * @env_head: singly linked list of environment vars
 * @alias_head: singly linked list of aliases
 * Description: This structures hold all variables that passed into
 * other functions.
 */
typedef struct args
{
	char **argv;
	char *buffer;
	char **params;
	char *nextCommand;
	unsigned int argsCap;
	unsigned int lineCount;
	unsigned int tokCount;
	int status;
	list_t *env_head;
	list_t *alias_head;
} arg_t;

/**
 * struct bf - structure containing builtin functions
 * @name: name of builtin function
 * @func: pointer to builtin functions
 */
typedef struct bf
{
	char *name;
	void (*func)(arg_t *);
} bf_t;

/* main.c */
arg_t *init_arg(char **argv, char **env);
arg_t *init_arg(char **argv, char **env);
void sigint_handler(int __attribute__((unused)) s);
int process_string(arg_t *args);
char **_realloc(char **ptr, unsigned int old_size, unsigned int new_size);

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
int _strcmp(char *s1, char *s2);
int _strcmp_n(char *s1, char *s2, int n);
int _atoi(char *s);
int flush_buffer(char *buffer, int *index);
int print_arg(char *arg);
void get_type(char *format, int *index);
int _printf(const char *, ...);
char *_strchr(char *s, char c);
char *_strdup(char *str);
char *get_arg(char type, ...);
char *str_concat(char *s1, char *s2);

/* other functions */
void run_command(arg_t *);
/* void *_realloc(char **ptr, unsigned int old_size, unsigned int new_size); */
void _printenv(arg_t *);
void sigint_handler(int);
char *_getenv(char *name, arg_t *args);
void _setenv(arg_t *args);
void _unsetenv(arg_t *args);
char *get_file(arg_t *args);
void (*get_builtin(arg_t *args))(arg_t *);
void _myExit(arg_t *args);
void _cd(arg_t *args);
void _alias(arg_t *args);
void set_alias(char *name, arg_t *args);
void make_alias(char *name, char *val, arg_t *args);
void print_alias(char *name, arg_t *args);
void print_all_aliases(arg_t *args);
void print_list_env(list_t *);
void print_list_alias(list_t *);
void free_args(arg_t *args);
void write_error(arg_t *args, char *msg);
void free_args(arg_t *args);
void _clear(arg_t *args);

/* getfile1.c */
char *get_char(char c);
char *get_string(char *s);
char *get_number(int n);
char *get_arg(char type, ...);
char *get_binary(unsigned int n);
char *get_rev(char *s);
char *get_rot13(char *s);
char *str_concat(char *, char *);
char *string_nconcat(char *, char *, unsigned int);

/* _strtok.c */
int isDelim(char c, char *delim);
char *_strtok(char *str, char *delim, char **savePtr);


#endif
