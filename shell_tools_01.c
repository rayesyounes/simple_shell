#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * fork_command - forks and execute process to run command
 * @info: params & return info
 * Return: void
 */

void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, return_environ(info)) == -1)
		{
			free_data(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				put_error(info, "Permission denied\n");
		}
	}
}

/**
 * find_command - find the command path
 * @info: params & return info
 * Return: void
 */

void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = find_path(info, get_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interact(info) ||
			 get_environ(info, "PATH=") ||
			 info->argv[0][0] == '/') &&
			command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			put_error(info, "not found\n");
		}
	}
}
