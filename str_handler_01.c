#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * str_copy - copy a string
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *str_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_duplicate - duplicate a string
 * @str: string to duplicate
 * Return: pointer to duplicated string
 */

char *str_duplicate(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (len++; len--;)
		ret[len] = *--str;

	return (ret);
}

/**
 * put_str - print string
 * @str: string printed
 * Return: void
 */

void put_str(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		put_char(str[i]);
		i++;
	}
}

/**
 * put_char - write char
 * @c: char to print
 * Return: 1 (Success), -1 (Fail)
 */

int put_char(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}
