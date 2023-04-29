#include "shell.h"

arg_t *init_arg(char **argv, char **env);
/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: Null terminated argument list
 * @env: Null terminated environment variables list
 *
 * Return: 0 on success
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	arg_t *args = NULL;
	int cond = -2, status;
	unsigned int i;
	char *state = NULL;
	size_t size = BUFFER_SIZE;

	args = init_arg(argv, env);
	if (!args)
		exit(-1);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (cond == -1)
		{
			status = args->status;
			_printf("($) \n");
			free_args(args);
			return (status);
		}
		for (i = 0; i < BUFFER_SIZE; i++)
			(args->buffer)[i] = 0;
		args->tokCount = 0;
		if (isatty(STDIN_FILENO))
			_printf("($): ");
		/*cond = _getline(params);*/
		cond = getline(&args->buffer, &size, stdin);
		args->lineCount++;
		if (cond == -1 && _strlen(args->buffer) == 0)
		{
			status = args->status;
			free_args(args);
			return (status);
		}
		state = NULL;
		args->nextCommand = _strtok(args->buffer, ";\n", &state);
		while (args->nextCommand)
		{
			args->tokCount = process_string(args);
			if (args->tokCount == 0)
				break;
			run_command(args);
			for (i = 0; i < args->argsCap; i++)
			{
				free(args->params[i]);
				args->params[i] = NULL;
			}
			args->tokCount = 0;
			free(args->nextCommand);
			args->nextCommand = _strtok(args->buffer, ";\n",
						      &state);
		}
	}
}
/**
 * init_arg - initialize args
 * @argv: command line argument
 * @env: environment variables
 * Return: arg on success
 */
arg_t *init_arg(char **argv, char **env)
{
	unsigned int i;
	char *eqs = NULL;
	arg_t *args = malloc(sizeof(*args));

	if (!args)
		return (NULL);
	args->argsCap = 10;
	args->lineCount = 0;
	args->tokCount = 0;
	args->status = 0;
	args->argv = argv;
	args->nextCommand = NULL;
	args->buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!(args->buffer))
	{
		free(args);
		exit(-1);
	}
	for (i = 0; i < BUFFER_SIZE; i++)
		args->buffer[i] = 0;
	args->params = malloc(sizeof(char *) * args->argsCap);
	if (!(args->params))
	{
		free(args->buffer);
		free(args);
		exit(-1);
	}
	for (i = 0; i < args->argsCap; i++)
		args->params[i] = NULL;
	args->env_head = NULL;
	for (i = 0; env[i]; i++)
	{
		eqs = _strchr(env[i], '=');
		*eqs = '\0';
		args->env_head = add_node(&(args->env_head),
					    env[i], eqs + 1);
		if (!(args->env_head))
		{
			free(args->buffer);
			free(args->params);
			free_list(args->env_head);
			free(args);
			exit(-1);
		}
	}
	args->alias_head = NULL;
	return (args);
}
