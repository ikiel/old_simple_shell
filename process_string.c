#include "shell.h"

/**
 * process_string - process the next command into string tokens
 * @args: parameters
 *
 * Return: number of tokens
 */
int process_string(arg_t *args)
{
	char *token = NULL, *state = NULL;
	char *alias = NULL, *state_2 = NULL, *val;
	list_t *node;

	token = _strtok(args->nextCommand, " \n\t", &state);
	if (!token)
	{
		args->tokCount = 0;
		return (0);
	}
	node = get_node(args->alias_head, token);
	if (node != NULL)
	{
		free(token);
		token = NULL;
		alias = _strdup(node->val);
		if (!alias)
		{
			write(STDERR_FILENO,
			      "alias expansion malloc error\n", 18);
			free_args(args);
			exit(-1);
		}
		val = _strtok(alias, " \n\t", &state_2);
		(args->params)[(args->tokCount)++] = val;
		while (val)
		{
			val = _strtok(alias, " ", &state_2);
			(args->params)[(args->tokCount)++] = val;
		}
		free(alias);
	}
	else
		(args->params)[(args->tokCount)++] = token;
	token = _strtok(args->nextCommand, " \n\t", &state);
	args->params[args->tokCount++] = token;
	while (token)
	{
		token = _strtok(args->nextCommand, " \n\t", &state);
		(args->params)[(args->tokCount)++] = token;
		if (args->tokCount == args->argsCap)
		{
			args->argsCap += 10;
			args->params = _realloc(args->params,
						args->argsCap - 10,
						args->argsCap);
			if (!(args->params))
			{
				write(STDERR_FILENO, "realloc error\n", 14);
				free_args(args);
				exit(-1);
			}
		}
	}
	return (args->tokCount - 1);
}
