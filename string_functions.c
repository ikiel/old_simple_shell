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

/**
 *_strlen - returns the length of a string
 *@s: string
 *Return: 0 if null, else length without null byte
 */
int _strlen(char *s)
{
	int length = 0;

	if (s == NULL)
	{
		return (0);
	}

	for (length = 0; s[length] != '\0'; length++)
		;
	return (length);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: int less than, equal to, or greater than 0 if s1 is, respectively
 * less than, equal to, or greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	int result = 0;

	do {
		result = *s1 - *s2;
		if (*s1 == 0 || *s2 == 0)
			break;
		s1++;
		s2++;
	} while (result == 0);

	return (result);
}

/**
 * _atoi - turn a string into an int
 * @s: string to evaluate
 * Return: n the value of the first number in the string
 */
int _atoi(char *s)
{
	int n, tmp, len, mul = 1;

	n = 0;
	tmp = 0;

	len = _strlen(s);
	len--;
	while (len >= 0)
	{
		tmp = n;
		n = n + (s[len] - '0') * mul;
		if (n < tmp || n > INT_MAX)
			return (-1);
		len--;
		mul *= 10;
	}
	return (n);
}

/**
 * _strcmp_n - compares n bytes of two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes to comp
 */
int _strcmp_n(char *s1, char *s2, int n)
{
	int i = 0, res = *s1 - *s2;

	while (i <= n)
	{
		res = *(s1++) - *(s2++);
		if (res != 0)
			break;
		i++;
	}

	return (res);
}

/**
 * _strdup - copy a string to a new allocated block of memory
 * @str: string
 *
 * Return: pointer to duplicated string, NULL if insufficient memory
 */

char *_strdup(char *str)
{
	int len = 0; /* index of terminating null byte */
	char *ptr = NULL;

	if (!str)
		return (NULL);
	while (*str)
	{
		len++;
		str++;
	}
	ptr = (char *) malloc(sizeof(char) * (len + 1));
	if (ptr)
	{
		while (len >= 0)
			*(ptr + len--) = *(str--);
	}
	return (ptr);
}

char *str_concat(char *s1, char *s2)
{
	char *ptr;
	int i = 0;
	int j = 0;
	int x = 0;

	if (s1 == NULL)
	{
		s1 = "";
	}
	if (s2 == NULL)
	{
		s2 = "";
	}
	while (s1[i] != '\0')
	{
		i++;
	}
	while (s2[j] != '\0')
	{
		j++;
	}
	ptr = malloc((i * sizeof(char)) + (j * sizeof(char)) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; s1[i] != '\0'; i++)
	{
		ptr[i] = s1[i];
		x++;
	}
	for (j = 0; s2[j] != '\0'; j++)
	{
		ptr[x] = s2[j];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}

/**
 * _strchr - locates a character in a string
 * @s: where to start looking
 * @c: values to find
 *
 * Return: pointer to begining of mem area
 */
char *_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (0);
}

