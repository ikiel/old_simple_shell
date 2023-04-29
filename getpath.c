#include "shell.h"

/**
 * get_file - get correct path to a command file
 * @args: parameters
 *
 * Return: string of valid path to command file, NULL if not found
 * The string needs to be freed
 */
char *get_file(arg_t *args)
{
	char *path = NULL;
	char *exePath = NULL, *exeArg = NULL, *tmp = NULL;
	char *state = NULL;

	if (access(args->params[0], F_OK | X_OK) == 0)
	{
		free(path);
		return (_strdup(args->params[0]));
	}
	if (errno == EACCES)
	{
		args->status = 126;
		write_error(args, "Permission denied\n");
		return (NULL);
	}
	path = _getenv("PATH", args);
	if (!path)
	{
		write_error(args, "not found\n");
		return (NULL);
	}
	exePath = _strtok(path, ":", &state);
	while (exePath)
	{
		tmp = exeArg;
		exeArg = str_concat(exePath, "/");
		free(tmp);
		tmp = exeArg;
		exeArg = str_concat(exeArg, args->params[0]);
		free(tmp);
		if (access(exeArg, F_OK) == 0)
		{
			free(path);
			free(exePath);
			return (exeArg);
		}
		free(exePath);
		exePath = _strtok(path, ":", &state);
	}
	args->status = 127;
	write_error(args, "not found\n");
	free(path);
	free(exePath);
	free(exeArg);
	return (NULL);
}
