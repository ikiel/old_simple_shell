#include "shell.h"

/**
 * tokenize - breaks a line into tokens
 * @str: the token
 * @args: where to store the tokens
 */
void tokenize(char *str, char **args)
{
	char *token;
	int i = 0;

	token = strtok(str, " ");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
}
