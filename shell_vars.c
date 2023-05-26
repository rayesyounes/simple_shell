#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * chain - test if curr char in buffer
 * @info: struct
 * @buf: the char buffer
 * @p: adreese the current position
 * Return: 1 if chai delim, 0 if not
 */

int chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - check and continue chaining
 * @info: struct
 * @buf: char buffer
 * @p: adress current pos
 * @i: starting pos in buf
 * @len: len of buffer
 * Return: void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replace aliases in tokenize string
 * @info: params
 * Return: 1 if (replaced), 0 if not
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodestart_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_locat(node->str, '=');
		if (!p)
			return (0);
		p = str_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (0);
}

/**
 * replace_var - replace var in tokenized string
 * @info: params struct
 * Return: 1 (Success), 0 (Fail)
 */

int replace_var(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_compare(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]),
						str_duplicate(convert_nb(info->status, 10, 0)));
			continue;
		}
		if (!str_compare(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
						str_duplicate(convert_nb(getpid(), 10, 0)));
			continue;
		}
		node = nodestart_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_str(&(info->argv[i]), str_duplicate(str_locat(node->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[i], str_duplicate(""));
	}
	return (0);
}

/**
 * replace_str - replace string
 * @old: old one
 * @new: new one
 * Return: 1 if replaced, 0 if not
 */

int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
