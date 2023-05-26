#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * memo_set - fill memo with const byte
 * @s: pointer to memo area
 * @b: byte to fill
 * @n: amount of byte field
 * Return: pointer to area memo
 */

char *memo_set(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * free_strn - free string of strings
 * @s: string of strings
 * Return: void
 */

void free_strn(char **s)
{
	char **a = s;

	if (!s)
		return;

	while (*s)
		free(*s++);

	free(a);
}

/**
 * memo_reallocat - reallocation of block memo
 * @ptr: pointer to prev malloc
 * @old_size: size of prev block
 * @new_size: new block size
 * Return: pointer
 */

void *memo_reallocat(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}

/**
 * free_pointer - frees pointer and put null to the adresse
 * @ptr: adresse of pointer
 * Return: 1 (Success), 0 (FAIL)
 */

int free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
