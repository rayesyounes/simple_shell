#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * putin_str - prints input string
 * @str: string printed
 * Return: void
 */

void putin_str(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		putchar_stdr(str[i]);
		i++;
	}
}

/**
 * putchar_stdr - write char c to stderr
 * @c: char to print
 * Return: 1 (Success), -1 (Fail)
 */

int putchar_stdr(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}

/**
 * put_fd - write char c to a given fd
 * @c: char to print
 * @fd: fd to write
 * Return: 1 (Success), -1 (Fail)
 */

int put_fd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}

/**
 * putin_sfd - print input string
 * @str: string to print
 * @fd: fd to write
 * Return: number of char
 */

int putin_sfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
		i += put_fd(*str++, fd);

	return (i);
}
