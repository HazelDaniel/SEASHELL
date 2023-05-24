#include "utils/main.h"

int execute(char *command)
{
	char **args, *tmp, *res_tmp;
	int (*f)(char **list), ret_num = 0, indic, status;
	pid_t child_pid;

	args = _splitstr(command, " \t"), format_args(args);
	if (!(!args || !args[0]))
	{
		command = args[0];
		f = get_builtin(command);
		if (f)
		{
			ret_num = f(args + 1);
		}
		else
		{
			if (command && command[0] != '/' && command[0] != '.')
			{
				command = _trace(command);
				free(args[0]), args[0] = command, indic = 1;
			}
			if (!command || (access(command, F_OK) == -1))
			{
				if (errno == EACCES)
					ret_num = (create_error(args, 126));
				else
					ret_num = (create_error(args, 127));
			}
			else
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					if (indic)
						free(command);
					perror("Error forking child:");
					return (1);
				}
				if (child_pid == 0)
				{
					execve(command, args, new_environ);
					if (errno == EACCES)
						ret_num = (create_error(args, 126));
					if (create_ex_stat(ret_num))
						return(1);
					cleanup(), _exit(ret_num);
				}
				else
				{
					wait(&status);
					ret_num = WEXITSTATUS(status);
					if (create_ex_stat(status))
						return(1);
				}
			}
			if (indic)
				free(command);
		}
	}

	if (create_ex_stat(ret_num))
		return (1);
	return (ret_num);
}

/**
 * create_ex_stat - a function that
 * sets the exit status of a process
 * to a shell variable $?
 * @status: a parameter of type int
 * Return: int
 **/
int create_ex_stat(int status)
{
	char *tmp, *res;

	tmp = _itoa(status);
	if (!tmp)
		return (1);
	res = malloc(_strlen(tmp) + 3);
	if (!res)
	{
		free(tmp);
		return (1);
	}
	res[0] = '?', res[1] = '=';
	_memcpy(tmp, res + 2, _strlen(tmp));
	if (!_setvar(res))
	{
		free(tmp), free(res);
		return (1);
	}
	free(tmp), free(res);

	return (0);
}
