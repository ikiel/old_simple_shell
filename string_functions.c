#include "shell.h"

/**
 * _strcpy - copies string to buffer
 * @dest: buffer
 * @src: string
 * Return: pointer to @dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	i = -1;

	do {
		i++;
		if (src[i] != '\n')
			dest[i] = src[i];
	} while (src[i] != '\0');

	return (dest);
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string to standard output
 * @str: string to print
 */

void _puts(char *str)
{
	int i;

	i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

	_putchar('\n');
}

/**
 * prompt - prints the shell prompt
 * @str: string to print
 */

void prompt(char *str)
{
	int i;

	i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
