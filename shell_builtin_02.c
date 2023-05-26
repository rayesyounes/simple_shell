#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 *_myhelp - display help
 *@info: struct for potential arguments
 *Return: 0 (Success)
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	put_str("help call work, function net yet implemented \n");
	if (0)
		put_str(*arg_arr);
	return (0);
}
