#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * _myhistory - display history
 * @info: struct contains all arguments
 * Return: 0 (Success)
 */

int _myhistory(info_t *info)
{
	put_list(info->history);
	return (0);
}

/**
 * unset_alias - unset alias
 * @info: struct contains all arguments
 * @str: alias string
 * Return: 0 (Success), 1 (Fail)
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = str_locat(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = del_node_at(&(info->alias),
								get_node_index(info->alias,
												nodestart_with(info->alias, str, -1)));
	*p = c;

	return (ret);
}

/**
 * set_alias - set alias
 * @info: struct contains all arguments
 * @str: alias string
 * Return: 0 (Success), 1 (Fail)
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = str_locat(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * put_alias - print alias
 * @node: alias linked list
 * Return: 0 (Success), 1 (Fail)
 */

int put_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_locat(node->str, '=');
		for (a = node->str; a <= p; a++)
			put_char(*a);

		put_char('\'');
		put_str(p + 1);
		put_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - alias built
 * @info: struct contains all arguments
 * Return: 0 (Success)
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			put_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 0; info->argv[i]; i++)
	{
		p = str_locat(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			put_alias(nodestart_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
