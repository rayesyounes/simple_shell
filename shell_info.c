#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * clear_data - init info struct
 * @info: struct of params
 * Return: void
 */

void clear_data(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_data - set info
 * @info: struct of params
 * @av: arguments
 * Return: void
 */

void set_data(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strto_word_1(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_var(info);
	}
}

/**
 * free_data - free all info from struct
 * @info: struct of params
 * @all: true if free all
 * Return: void
 */

void free_data(info_t *info, int all)
{
	free_strn(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_strn(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		put_char(BUF_FLUSH);
	}
}
