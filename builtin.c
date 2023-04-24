#include "shell_demo.h"

/**
 * change_directory - changes user's working directory
 * @args: user command
 *
 * Return: nothing
 */

void change_directory(char **args)
{
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
	}
	else
	{
		chdir(args[1]);
	}
	continue;
}
