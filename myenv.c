#include "shell.h"

/**
 * _myenv - prints my present environment
 * @info: Structure containing potential arguments,
 *	for maintaining constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _mysetenv - Initiailize new or modify existing environment var.
 * @info: Structure containing potential arguments,
 *        for maintaining constant function prototype.
 *  Return: 0 Always
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

		return (1);
}

/**
 * _myunsetenv - Removes environment variable
 * @info: Structure containing potential arguments,
 *        for maintaining constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs("Very few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments
 *	for maintaining constant function prototype.
 * @name: environment variable name
 *
 * Return: environment value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);

		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - populates environment  list
 * @info: Structure containing potential arguments,
 *          for maintaining constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&node, environ[k], 0);
	info->env = node;

	return (0);
}
