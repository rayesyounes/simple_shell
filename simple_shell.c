#include "shell.h"

/* rayesyounes - spoutnikrs */

/**
 *main - Entry point
 *@ac: len of av
 *@av: number of params
 *Return: Always 0 (Success)
 */

int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				putin_str(av[0]);
				putin_str(": 0: Can't open ");
				putin_str(av[1]);
				putchar_stdr('\n');
				putchar_stdr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_environ_list(info);
	read_history(info);
	shell_loop(info, av);
	return (EXIT_SUCCESS);
}
