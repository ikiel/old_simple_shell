#include "shell_demo.h"

/**
 * main - test super simple shell
 *
 * Return: 0
 */

int main(void)
{
	char input[MAX_LINE_LENGTH];
	char *args[MAX_LINE_LENGTH / 2 + 1];
	char *token;
	pid_t child_pid;
	int i = 0, should_run = 1;

	while (should_run)
	{

		printf("#cisfun$>  ");
		fflush(stdout);

		fgets(input, MAX_LINE_LENGTH, stdin);

		input[strcspn(input, "\n")] = 0;

		token = strtok(input, " ");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
			should_run = 0;
			break;
		}
		else if (strcmp(args[0], "cd") == 0)
			change_directory(args);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
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
			waitpid(child_pid, NULL, 0);
	}

	return (0);
}
