#include "utils/main.h"

int (*get_builtin(char *command))(char **list)
{
	builtin_t funcs[] = {
		{ "exit", handle_exit },
		{ "env", handle_print_env },
		{ "setenv", handle_set_env },
		{ "unsetenv", handle_unset_env },
		{ "cd", handle_cd },
		{ "alias", handle_alias },
		{ "help", handle_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (!_strcmp(funcs[i].name, command))
			break;
	}
	return (funcs[i].f);
}

int exit_(char *status, char **list)
{
	int i, dig_len = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (status)
	{
		if (status[0] == '+')
			i = 1, dig_len++;
		for (; status[i]; i++)
		{
			if (i <= dig_len && status[i] >= '0' && status[i] <= '9')
				num = (num * 10) + (status[i] - '0');
			else
				return (create_error(--list, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--list, 2));
	list -= 1;
	_freenv();
	free_aliases(aliases);
	exit(num);
}

int cd(char *loc, char **list)
{
	char *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (loc)
	{
		if (*loc == '-' || _strcmp(loc, "--") == 0)
		{
			if ((loc[1] == '-' && loc[2] == '\0') ||
					loc[1] == '\0')
			{
				if (_getenv("OLDPWD"))
					(chdir(_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(list, 2));
			}
		}
		else
		{
			if (stat(loc, &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(loc);
			else
			{
				free(oldpwd);
				return (create_error(list, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir((_getenv("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	// dir_info = malloc(_strlen("OLDPWD") + _strlen(oldpwd) + 2);
	// if (!dir_info)
	// 	return (-1);
	// _memcpy("OLDPWD", dir_info, _strlen("OLDPWD"));
	// _memcpy("=", dir_info + _strlen("OLDPWD"), 1);
	// _memcpy(oldpwd, dir_info + _strlen("OLDPWD") + 1, _strlen(oldpwd));
	if (_setenv("OLDPWD", oldpwd) == -1)
		return (-1);

	// free(dir_info);
	// dir_info = malloc(_strlen("PWD") + _strlen(pwd) + 2);
	// if (!dir_info)
	// 	return (-1);
	// _memcpy("PWD", dir_info, _strlen("PWD"));
	// _memcpy("=", dir_info + _strlen("PWD"), 1);
	// _memcpy(pwd, dir_info + _strlen("PWD") + 1, _strlen(pwd));
	if (_setenv("PWD", pwd) == -1)
		return (-1);
	if (loc && loc[0] == '-' && loc[1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd), free(pwd);
	return (0);
}

int help(char *command)
{
	if (!command)
		help_all();
	else if (!_strcmp(command, "alias"))
		help_alias();
	else if (!_strcmp(command, "cd"))
		help_cd();
	else if (!_strcmp(command, "exit"))
		help_exit();
	else if (!_strcmp(command, "env"))
		help_env();
	else if (!_strcmp(command, "setenv"))
		help_setenv();
	else if (!_strcmp(command, "unsetenv"))
		help_unsetenv();
	else if (!_strcmp(command, "help"))
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
