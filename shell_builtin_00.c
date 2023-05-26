#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * _myexit - exit the shell
 * @info: struct for potential arguments
 * Return: exit only or with status given by the user
 */

int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = errato_int(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			put_error(info, "Ellegal number: ");
			putin_str(info->argv[1]);
			putchar_stdr('\n');
			return (1);
		}
		info->err_num = errato_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change current dir
 * @info: struct for potential arguments
 * Return: 0 (Success)
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		put_str("Todo: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_environ(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_environ(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_compare(info->argv[1], "-") == 0)
	{
		if (!get_environ(info, "OLDPWD="))
		{
			put_str(s);
			put_char('\n');
			return (1);
		}
		put_str(get_environ(info, "OLDPWD=")), put_char('\n');
		chdir_ret = chdir((dir = get_environ(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		put_error(info, "Folder does not exist ");
		putin_str(info->argv[1]), putchar_stdr('\n');
	}
	else
	{
		setnew_environ(info, "OLDPWD", get_environ(info, "PWD"));
		setnew_environ(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
