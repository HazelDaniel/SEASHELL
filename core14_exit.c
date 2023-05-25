#include "utils/main.h"

/**
  * exec_on_exit - exit handler
  * Return: void .
 */
void exec_on_exit(void)
{
	int access_n, read_n, count = 0, i;
	ssize_t fd;
	char *buff = NULL, *fd_str, **exec_list;

	if (!callpwd)
		return;
	access_n = access(callpwd, F_OK);
	if (access_n != 0)
	{
		puts("directory does not exist!");
		return;
	}
	fd = open(callpwd, O_RDONLY);
	if (fd == -1)
	{
		printf("can't open directory :%s\n", callpwd);
		return;
	}
	buff = malloc(BUFF_LEN * sizeof(char));
	while ((read_n = read(fd, buff, BUFF_LEN)) > 0)
	{
		if (count >= _strlen(buff) - 1)
		{
			buff = _realloc(buff, _strlen(buff) + 1, _strlen(buff) + 121);
			if (!buff)
			{
				free(callpwd);
				return;
			}
		}
		count++;
	}
	if (read_n == -1)
		puts("error with the read");
	exec_list = _splitstr(buff, "\n");

	for (i = 0; exec_list[i]; i++)
		execute(exec_list[i]);

	fd_str = _itoa(fd);
	if (close(fd) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't close fd ", 22);
	write(STDERR_FILENO, fd_str, _strlen(fd_str));
	write(STDERR_FILENO, "\n", 1);

	free(callpwd), free(fd_str), cleanup();
}

/**
  * set_exec_dir - the function name
  * @argv: parameter of type (char *)[].
  * Return: void .
 */
void set_exec_dir(char *argv[])
{
	if (_len_p((void *)argv) == 2)
	{
		callpwd = _getenv("PWD");
		callpwd = _realloc(callpwd, _strlen(callpwd) + 1, _strlen(callpwd) + _strlen(argv[1]) + 2);
		_memcpy("/", callpwd + _strlen(callpwd), 1);
		_memcpy(argv[1], callpwd + _strlen(callpwd), _strlen(argv[1]));
	}
}
