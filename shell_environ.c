#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * _myenv - print env
 * @info: struct of params
 * Return: 0 (Success)
 */

int _myenv(info_t *info)
{
	put_list_str(info->env);
	return (0);
}

/**
 * get_environ - get env value
 * @info: struct of params
 * @name: env name
 * Return: env value
 */

char *get_environ(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environ - create env variable
 * @info: struct of params
 * Return: 0 (Success)
 */

int set_environ(info_t *info)
{
	if (info->argc != 3)
	{
		putin_str("Incorrect number of arguments\n");
		return (1);
	}
	if (setnew_environ(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * unset_environ - create env variable
 * @info: struct of params
 * Return: 0 (Success)
 */

int unset_environ(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		putin_str("To few arguments.\n");
		return (1);
	}
	for (i = 0; i <= info->argc; i++)
		remove_environ(info, info->argv[i]);

	return (0);
}

/**
 * populate_environ_list - env linked list
 * @info: struct of params
 * Return: 0 (Success)
 */

int populate_environ_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
