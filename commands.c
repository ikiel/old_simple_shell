#include"shell.h"

/**
 * run_command - searches path dirs for command and execs
 * @args: parameters
 */
void run_command(arg_t *args)
{
	char *exeFile = NULL;
	pid_t pid;
	void (*buildin)(arg_t *);

	buildin = get_builtin(args);
	if (buildin)
	{
		buildin(args);
		return;
	}
	exeFile = get_file(args);
	if (!exeFile)
	{
		return;
	}
	pid = fork();
	if (pid < 0)
	{
		free_args(args);
		exit(98);
	}
	else if (pid == 0)
	{
		execve(exeFile, args->params, NULL);
	}
	else
	{
		wait(&args->status);
		args->status = WEXITSTATUS(args->status);
		free(exeFile);
	}
}
