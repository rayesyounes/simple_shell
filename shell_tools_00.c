#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * shell_loop - main shell loop
 * @info: params & return info
 * @av: argument pointer from main
 * Return: 0 (Success), 1 (Error)
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(info);
		if (interact(info))
			put_str("Spoutnikrs-rayesyounes$: ");
		putchar_stdr(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_data(info, av);
			builtin_ret = find_built(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (interact(info))
		{
			put_char('\n');
		}
		free_data(info, 0);
	}
	write_history(info);
	free_data(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_built - find builtin command
 * @info: params & return info
 * Return: -1 if not found, 0 if execute success
 * 1 if found and execute not success
 * -2 if exit
 */

int find_built(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", set_environ},
		{"unsetenv", unset_environ},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (str_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}
