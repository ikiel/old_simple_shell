#include "shell.h"

/**
 * _alias - Implements the "alias" shell command.
 * @args: pointer to arg_t struct with the shell state and args.
 *
 */

void _alias(arg_t *args)
{
	unsigned int i;

	if (args->tokCount == 1)
	{
		print_all_aliases(args);
		return;
	}
	for (i = 1; i < args->tokCount; i++)
	{
		if (_strchr(args->params[i], '='))
			set_alias(args->params[i], args);
		else
			print_alias(args->params[i], args);
	}
}

/**
 * set_alias - creates a new alias or updates an existing one
 * @name: the name of the alias to set
 * @args: shell state
 *
 * Return: void
 */
void set_alias(char *name, arg_t *args)
{
	char *val, *tmp = NULL;
	unsigned int i = 0, j = 1;

	while (name[i] && name[i] != '=')
		i++;
	if (name[i + 1] == '\'')
	{
		if (_strchr(&name[i + 2], '\''))
		{
			tmp = _strchr(&name[i + 2], '\'');
			*tmp = '\0';
			val = _strdup(&name[i + 2]);
			if (tmp[1] != '\0')
			{
				while (tmp[j] &&
					(tmp[j] == ' ' || tmp[j] == '\t' || tmp[j] == '\n'))
					j++;
				if (tmp[j] != '\0')
					set_alias(&tmp[j], args);
			}
		}
		else
		{
			_printf("Usage: alias name='value' [...]\n");
			return;
		}
	}
	else
		val = _strdup(&name[i + 1]);
	name[i] = '\0'; /* set = to terminater */
	make_alias(name, val, args);
}

/**
 * make_alias - creates a new alias and adds it to the alias list
 * @name: name of the alias
 * @val: value of the alias
 * @args: parameter struct containing the alias list
 */

void make_alias(char *name, char *val, arg_t *args)
{
	list_t *h = args->alias_head;

	while (h)
	{
		if (!_strcmp(name, h->str))
		{
			free(h->val);
			h->val = val;
			h->valLen = _strlen(val);
			args->status = 0;
			return;
		}
		h = h->next;
	}
	/* env var DNE */

	args->alias_head = add_node(&(args->alias_head), name, val);
	free(val);
	args->status = 0;
}
