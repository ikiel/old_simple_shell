#include "shell.h"

/**
 * _cd - change the current working directory
 * @args: shell arguments
 *
 * Return: void
 */
void _cd(arg_t *args)
{
	char *target = NULL, cwd[1024];
	char **tmpArgs = NULL, **originArgs = NULL;
	int i;

	if (args->tokCount == 1)
	{
		target = _getenv("HOME", args);
		if (!target)
		{
			args->status = 0;
			return;
		}
	}
	else if (args->params[1][0] == '-')
	{
		if (!_strcmp(args->params[1], "-"))
		{
			target = _getenv("OLDPWD", args);
			if (!target)
			{
				args->status = 0;
				target = _getenv("PWD", args);
				_printf("%s\n", target);
				free(target);
				return;
			}
			_printf("%s\n", target);
		}
		else
		{
			args->status = 2;
			_printf("%s: %d: cd: Illegal option %c%c\n",
				args->argv[0], args->lineCount,
				'-', args->params[1][1]);
			return;
		}
	}
	else
	{
		target = _strdup(args->params[1]);
		if (!target)
		{
			write(STDERR_FILENO, "cd target malloc error\n", 18);
			exit(-1);
		}
	}
	i = chdir(target);
	if (i)
	{
		write_error(args, "can't cd to ");
		write(STDERR_FILENO, target, _strlen(target));
		write(STDERR_FILENO, "\n", 1);
		args->status = 0;
		free(target);
		return;
	}
	free(target);
	tmpArgs = malloc(sizeof(char *) * 3);
	if (!tmpArgs)
		exit(-1);
	originArgs = args->params;
	args->params = tmpArgs;
	args->tokCount = 3;

	/* set OLDPWD to the current PWD */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("OLDPWD");
	if (!tmpArgs[0] || !tmpArgs[1])
	{
		write(STDERR_FILENO, "cd old PWD malloc error\n", 18);
		free_args(args);
		exit(-1);
	}
	tmpArgs[2] = _getenv("PWD", args);
	_setenv(args);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);

	/* set PWD to the target wd */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("PWD");
	tmpArgs[2] = _strdup(getcwd(cwd, 1024));
	if (!tmpArgs[0] || !tmpArgs[1] || !tmpArgs[2])
	{
		write(STDERR_FILENO, "cd new PWD malloc error\n", 18);
		free_args(args);
		exit(-1);
	}
	_setenv(args);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);
	free(tmpArgs);
	/* reset params */
	args->params = originArgs;
}
