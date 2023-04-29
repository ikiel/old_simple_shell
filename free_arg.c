#include "shell.h"

/**
 * free_args - Frees the memory allocated for the param_t structure.
 * 
 * @args: pointer to the param_t structure to free
 *
 */
void free_args(arg_t *args)
{
	unsigned int i;

	if (args->buffer)
		free(args->buffer);
	if (args->nextCommand)
		free(args->nextCommand);
	free_list(args->env_head);
	free_list(args->alias_head);

	for (i = 0; args->params[i]; i++)
		free(args->params[i]);
	free(args->params);
	free(args);
}
