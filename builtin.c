#include "shell.h"

/**
 * get_builtin - Get built-in function
 * @args: Pointer to the arg_t struct containing shell arguments
 *
 * Description: Searches for a built-in function based on the first argument
 * in the arg_t struct
 *
 * Return: Function pointer to the built-in function. NULL if not found
 */

void (*get_builtin(arg_t *args))(arg_t *)
{
	bf_t bfs[] = {
		{"exit", _myExit},
		{"clear", _clear},
		{"env", _printenv},
		{"setenv", _setenv},
		{"cd", _cd},
		{"unsetenv", _unsetenv},
		{"alias", _alias},
		{NULL, NULL},
	};
	bf_t *bf = bfs;

	while (bf->name)
	{
		if (!_strcmp(args->params[0], bf->name))
			return (bf->func);
		bf++;
	}
	return (NULL);
}

/**
 * _clear - clears the terminal screen
 * @args: parameters
 *
 * Return: void
 */
void _clear(arg_t *args)
{
	(void)args;
	_printf("\033[2J\033[1;1H");
}

/**
 * validNum - check if the string is a valid number
 * @s: the string
 *
 * Return: 0 if false, 1 otherwise
 */
int validNum(char *s)
{
	while (*s)
	{
		if (*s > '9' || *s < '0')
			return (0);
		s++;
	}
	return (1);
}

/**
 * _myExit - builtin exit function
 * @args: parameters
 */
void _myExit(arg_t *args)
{
	int status = 0;

	if (!args->params[1])
	{
		status = args->status;
		free_args(args);
		exit(status);
	}
	if (validNum(args->params[1]))
	{
		status = _atoi((args->params)[1]);
		if (status == -1)
		{
			write_error(args, "Illegal number: ");
			write(STDERR_FILENO, args->params[1],
			      _strlen(args->params[1]));
			write(STDERR_FILENO, "\n", 1);
			args->status = 2;
			return;
		}
		free_args(args);
		exit(status);
	}
	else
	{
		args->status = 2;
		write_error(args, "Illegal number: ");
		write(STDERR_FILENO, args->params[1],
		      _strlen(args->params[1]));
		write(STDERR_FILENO, "\n", 1);
	}
}
