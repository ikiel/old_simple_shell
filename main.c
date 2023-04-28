#include "shell.h"

/**
 * main - the main shell
 * Return: Always 0 (success)
 */
int main(void)
{
	int read, should_run = 1;
	char *str = NULL;
	char **args = NULL;
	size_t len = 0;
	pid_t child_pid;

	while (should_run)
	{
		prompt("$ ");
		fflush(stdout);

		read = getline(&str, &len, stdin);
		if (read == -1)
		{
			perror("getline");
			free (str);
		}
		if (str[len] == '\n')
			str[len] = '\0';
		tokenize(str, args);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
		}
		else if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
				free(str);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(str);

	return (0);
}
