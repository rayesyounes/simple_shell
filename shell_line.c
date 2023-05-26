#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * _input_buf - buffer chained
 * @info: struct of params
 * @buffer: adress of buffer
 * @len: aress of len
 * Return: readed byte
 */

ssize_t _input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_int_handler);
#if USEget_line
		r = getline(buffer, &len_p, stdin);
#else
		r = get_line(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			del_comment(*buffer);
			build_history(info, *buffer, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets line - the new line
 * @info: struct of params
 * Return: readed byte
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buffer_p = &(info->arg), *p;

	put_char(BUF_FLUSH);
	r = _input_buf(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;
		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buffer_p = p;
		return (str_length(p));
	}
	*buffer_p = buffer;
	return (r);
}

/**
 * _read_buf - read a buffer
 * @info: struct of params
 * @buf: buffer
 * @i: size
 * Return: r
 */

ssize_t _read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets next line
 * @info: struct of params
 * @ptr: adress of buffer
 * @lenght: size
 * Return: s
 */

int get_line(info_t *info, char **ptr, size_t *lenght)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL;
	char *new_p = NULL, *c;

	p = *ptr;
	if (p && lenght)
		s = *lenght;
	if (i == len)
		i = len = 0;

	r = _read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = str_locat(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = memo_reallocat(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		strn_concat(new_p, buffer + i, k - i);
	else
		strn_copy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;
	if (lenght)
		*lenght = s;
	*ptr = p;
	return (s);
}

/**
 * signal_int_handler - blocks ctr-c
 * @sig: signal number
 * Return: void
 */

void signal_int_handler(__attribute__((unused)) int sig)
{
	put_str("\n");
	put_str("Spoutnikrs-rayesyounes$: ");
	put_char(BUF_FLUSH);
}
