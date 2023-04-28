#include "shell.h"

/**
 * main - the main shell
 * 
 * Return: Always 0 (success)
 */
int main(void)
{
	int read, should_run = 1;
	char *str = NULL, *token, *dup_str;
	char **args;
	ssize_t len = 0;
	pid_t child_pid, parent_id;

	while (should_run)
	{
		printf("$ ");
		fflush(stdout);

		read = getline(&str, &len, stdin);
		if (read == -1)
			perror("getline");
		str[strcspn(str, "\n")];

		dup_str = strdup(str);
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
			}
		}
		else
		{
			wait(NULL);
		}
	}
}
