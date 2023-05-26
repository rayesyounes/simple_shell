#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * strn_copy - cpys a string
 * @dest: the destination string to copied
 * @src: source string
 * @n: amount char copied
 * Return: concat string
 */

char *strn_copy(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * strn_concat - concat 2 string
 * @dest: 1st string
 * @src: 2nd string
 * @n: amount of bytes used
 * Return: concat string
 */

char *strn_concat(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';

	return (s);
}

/**
 * str_locat - locat char n string
 * @s: string to parse
 * @c: char to look for
 * Return: pointer to the memory areas s
 */

char *str_locat(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
