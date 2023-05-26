#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * list_length - len of linked
 * @h: pointer 1st node
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listto_str - return arr string list str
 * @head: pointer 1st node
 * Return: arr of string
 */

char **listto_str(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs, *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * put_list - print elem of linked
 * @h: point 1st node
 * Return: size of node
 */

size_t put_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_str(convert_nb(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		put_str(h->str ? h->str : "(nil)");
		put_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodestart_with - return node start with prefix
 * @node: pointer 1st node
 * @prefix: string to match
 * @c: next char after prefix to much
 * Return: match node or null
 */

list_t *nodestart_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get index of node
 * @head: point 1st head
 * @node: point to node
 * Return: index of node
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
