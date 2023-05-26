#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 * get_history - get history
 * @info: struct
 * Return: history file
 */

char *get_history(info_t *info)
{
	char *buffer, *dir;

	dir = get_environ(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_length(dir) + str_length(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_copy(buffer, dir);
	str_concat(buffer, "/");
	str_concat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - create file append exiting file
 * @info: struct
 * Return: 1 (Success), -1 (Fail)
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		putin_sfd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read hist file
 * @info: struct
 * Return: sit when (Success), 0 (Fail)
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);

	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_node_at(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history - add entrys to history linked list
 * @info: struct
 * @buf: buffer
 * @linecount: histcount
 * Return: 0 (Success)
 */

int build_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumber history
 * @info: struct
 * Return: new history
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
