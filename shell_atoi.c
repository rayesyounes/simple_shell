#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * interact - check if shell is interactive
 * @info: pointer to the struct contains info
 * Return: 1 (interactive), 0 if not
 */

int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - check if is delim
 * @c: char to check
 * @delim: delim string
 * Return: 1 (true), 0 if not
 */

int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}

	return (0);
}

/**
 * is_alphabet - check if is alpha
 * @c: char to check
 * Return: 1 (true), 0 if not
 */

int is_alphabet(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * ato_int - convert string to int
 * @s: string to convert
 * Return: 0 if no number found, convert if any
 */

int ato_int(char *s)
{
	int sign = 1;
	unsigned int res = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (sign * res);
}
