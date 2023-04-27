#include "shell.h"

/**
 * toexit - to exit the shell
 * @arguments: a large structure for the arguments
 * Return: 1 or 2 based on exit status
 */

int toexit(args_t *arguments)
{
	int check_exit;

	if (arguments->argv[1])
	{
		check_exit = erratoi(arguments->argv[1]);
		if (check_exit == -1)
		{
			arguments->status = -2;
			print_error(arguments, "illegal number: ");
			_puts(arguments->argv[1]);
			_putchar('\n');
			return (1);
		}
		arguments->error_number = erratoi(arguments->argv[1]);
		return (-2);
	}
	arguments->error_number = -1;
	return (-2);
}

/**
 * tocd - changes current working directory of the process
 * @arguments: a large structure for the arguments
 * Return: Always 0 (success)
 */

int tocd(args_t arguments)
{
	char *str, *direc, buffer[MAX_WRITE_SIZE];
	int ret_chredir;

	str = getcwd(buffer, MAX_WRITE_SIZE);
	if (!str)
		perror(getcwd);
	if (!arguments->argv[1])
	{
		direc = _getenv(arguments, "HOME=");
		if (direc == NULL)
			ret_chredir = chdir((direc = _getenv(arguments, "PWD=")) ? direc : "/");
		else
			ret_chredir = chdir(direc);
	}
	else if (_strcmp(arguments->argv[1], "-") == 0)
	{
		if (_getenv(arguments, "OLDPWD=") == NULL)
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(arguments, "OLDPWD="));
		_putchar('\n');
		ret_chredir = chdir((direc = _getenv(arguments, "OLDPWD=")) ? direc : "/");
	}
	else
		ret_chredir = chdir(arguments->argv[1]);
	if (ret_chredir == -1)
	{
		print_error(arguments, "cannot change directory to ");
		_puts(arguments->argv[1]);
		_putchar('\n');
	}
	else
	{
		_setenv(arguments, "OLDPWD", _getenv(info, "PWD="));
		_setenv(arguments, "PWD", getcwd(buffer, MAX_WRITE_LINE));
	}
	return (0);
}
