#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @arguments: a large structure containing arguments
 * @buf: buffer address
 * @len: len address
 *
 * Return: number of bytes read
 */
ssize_t input_buf(arg_t *arguments, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			arguments->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(arguments, *buf, arguments->histcount++);
		}
	}
	return (r);
}

/**
 * get_input - gets a line without the \n
 * @arguments: a large structure of arguments
 *
 * Return: number of bytes read
 */
ssize_t get_input(arg_t *arguments)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(arguments->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(arguments, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(arguments, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(arguments, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			arguments->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = p;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @arguments: a large structure of arguments
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(arg_t *arguments, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(arguments->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * sigintHandler - to block ctrl + C
 * @sig_num: the number of the signal
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

