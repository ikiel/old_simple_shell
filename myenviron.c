#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the environment variable to retrieve
 * @args: pointer to the parameter structure containing the environment list
 *
 * Return: pointer to the value of the environment variable, or NULL
 */

char *_getenv(char *name, arg_t *args)
{
	list_t *ptr = args->env_head;

	while (ptr)
	{
		if (!_strcmp(name, ptr->str))
			return (_strdup(ptr->val));
		ptr = ptr->next;
	}
	return (NULL);
}

/**
 * _printenv - prints the environment
 * @args: parameters
 * Prints all the environment variables stored in args->env_head.
 * If no environment variables exist, prints an error message.
 *
 * Return: void
 */

void _printenv(arg_t *args)
{
	if (args->tokCount != 1)
	{
		_printf("env: %s: No such file or directory\n",
			args->params[1]);
		args->status = 2;
		return;
	}
	print_list_env(args->env_head);
	args->status = 0;
}

/**
 * print_list_env - print the environment variables
 * @head: pointer to the head of the environment list
*/
void print_list_env(list_t *head)
{
	if (head)
	{
		print_list_env(head->next);
		if (head->str)
			_printf("%s=%s\n", head->str, head->val);
	}
}

/**
 * _setenv - function searches the environment list to find the
 * environment variable name, and sets to the corresponding
 * value string.
 * @params: parameters
*/
void _setenv(arg_t *args)
{
	char *tmp = NULL;
	char *name = args->params[1], *value = args->params[2];
	list_t *h = args->env_head;

	if (args->tokCount != 3)
	{
		args->status = 0;
		return;
	}
	while (h)
	{
		if (_strcmp(name, h->str) == 0) /* env var exists */
		{
			tmp = h->val;
			free(tmp);
			h->val = _strdup(value);
			if (!h->val)
			{
				write(STDERR_FILENO, "setenv malloc error\n", 18);
				exit(-1);
			}
			h->valLen = _strlen(value);
			args->status = 0;
			return;
		}
		h = h->next;
	}
	/* env var DNE */
	args->env_head = add_node(&(args->env_head), name, value);
	args->status = 0;
}

/**
 * _unsetenv - function searches the environment list to find the
 * environment variable name and removes it.
 * @args: parameters
*/
void _unsetenv(arg_t *args)
{
	char *name = args->params[1];
	list_t *prev = NULL, *h = args->env_head;

	if (args->tokCount != 2)
	{
		args->status = 0;
		return;
	}
	while (h)
	{
		if (_strcmp(name, h->str) == 0) /* env var exists */
		{
			if (h == args->env_head)
				args->env_head = h->next;
			else
				prev->next = h->next;
			free(h->str);
			free(h->val);
			free(h);
			args->status = 0;
			return;
		}
		prev = h;
		h = h->next;
	}
	args->status = 0;
}
