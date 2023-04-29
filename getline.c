#include "shell.h"

/**
 * readline - read line of user input
 * @str: address to save obtained line
 * @len: length of line
 *
 * Return: result of getline
 */
int readline(char *str, size_t len)
{
	int read;

	read = getline(&str, &len, stdin);

	return (read);
}

/**
 * remove_newline - removes newline character from text
 * @str: the text
 *
 * Return: text without '\n'
 */
char *remove_newline(char *str)
{
	char newline[516];
	int i = 0, j = 0;

	while (str[i] != '\0')
	{
		if (str[i] != '\n')
		{
			newline[j] = str[i];
			j++;
		}
		i++;
	}
	newline[j] = '\0';
	str = newline;

	return (str);
}
