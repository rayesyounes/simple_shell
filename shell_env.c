#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * return_environ - return arr copy of environ
 * @info: struct of params
 * Return: 0 (Success)
 */

char **return_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listto_str(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * remove_environ - remove env variable
 * @info: struct of params
 * @var: string env property
 * Return: changed value
 */

int remove_environ(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = del_node_at(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * setnew_environ - set new env variable
 * @info: struct of params
 * @var: string env property
 * @value: value
 * Return: 0 (Success)
 */

int setnew_environ(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(str_length(var) + str_length(value) + 2);
	if (!buffer)
		return (1);

	str_copy(buffer, var);
	str_concat(buffer, "=");
	str_concat(buffer, value);
	node = info->env;
	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
