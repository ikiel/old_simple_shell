#include "shell.h"

/**
 * main - the main shell
 * Return: Always 0 (success)
 */
int main(void)
{
	int read, length, should_run = 1;
	char *str = NULL;
	char **args;
	size_t len = 0;
	pid_t child_pid;

	while (should_run)
	{
		prompt("$ ");
		fflush(stdout);

		read = getline(&str, &len, stdin);
		if (read == -1)
			perror("getline");
		length = _strlen(str);
		if (str[length - 1] == '\n')
			str[length - 1] = '\0';
		args = malloc(sizeof(char *) * len);
		tokenize(str, args);

		child_pid = fork();
		if (child_pid == -1)
			perror("fork");
		else if (child_pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
	free(str);
	free(args);

	return (0);
}
