#include "utils/main.h"

int handle_st_tilds(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN]);
int handle_st_dots(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN]);
int handle_st_hyp(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN]);

/**
  * get_builtin - a function that selects
	* a function to handle a matched command
  * @command: the command passed
  * @list: parameter of type char ** - the argv
	* implementation.
  * Return: int .
 */
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
		{"\n", handle_nothing},
		{"", handle_nothing},
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

/**
  * exit_ - a customized exit function
  * @status: parameter of type char *.
  * @list: parameter of type char **.
  * Return: int .
 */
int exit_(char *status, char **list)
{
	int i = 0, dig_len = 10;
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
		exit(0);
	}
	if (num > max - 1)
		return (create_error(--list, 2));
	list -= 1;
	_freenv();
	free_aliases(aliases);
	exit(num);
}

/**
  * cd - changes directory to a specified location
  * @loc: parameter of type char *.
  * @list: parameter of type char **.
  * Return: int .
 */
int cd(char *loc, char **list)
{
	char dir_buff[BUFF_LEN], new_dir_buff[BUFF_LEN], *pwd = NULL,
	*curr_cpy, *old_cpy, *parent, *res = NULL, prev_buff[BUFF_LEN];
	struct stat dir;
	int l_slash_oc = -1, x = -1;
	static char previous[BUFF_LEN] = "";

	old_cpy = getcwd(dir_buff, sizeof(dir_buff));
	if (_len_p((void *)list) == 1 && last_oc(is_graph, loc) < 0)
		free(loc), loc = NULL;
	if (loc)
	{
		if (is_start_str("..", loc))
		{
			if (handle_st_dots(&old_cpy, &curr_cpy, loc, list, previous) == -1)
				return (-1);
		}
		else if (is_start_str("~", loc))
		{
			if (handle_st_tilds(&old_cpy, &curr_cpy, loc, list, previous) == -1)
				return (-1);
		}
		else if (is_start_str("-", loc))
		{
			if (handle_st_hyp(&old_cpy, &curr_cpy, loc, list, previous) == -1)
				return (-1);
		}
		else if (chdir(loc) != 0)
			return (create_error(list, 2));
		curr_cpy = getcwd(new_dir_buff, sizeof(new_dir_buff));
	}
	else
	{
		if (chdir(_getenv("HOME")) != 0)
			return (create_error(list, 2));
		curr_cpy = getcwd(new_dir_buff, sizeof(new_dir_buff));
	}
	if (_setenv("OLDPWD", old_cpy) != 0)
		return (-1);
	old_cpy = _getenv("OLDPWD");
	_memcpy(old_cpy, previous, _strlen(old_cpy)), free(old_cpy), old_cpy = NULL;
	if (_setenv("PWD", curr_cpy) != 0)
		return (-1);

	return (0);
}

/**
  * help - prints out the guide for a command
	* or collection of commands
  * @command: parameter of type char *.
  * Return: int .
 */
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

/*
 * the algo for checking the parent directory:
 * this is based on the sloppy assumption that at any point
 * in the file system, you will always have a directory that
 * contains a forward slash , else we'll check for / first
 */
/**
  * handle_st_dots - a function that handles
	* cd arguments starting with dots
  * @old_cptr: parameter of type char **.
  * @curr_cptr: parameter of type char **.
  * @loc: parameter of type char *.
  * @args: parameter of type char **.
  * @prev: parameter of type char .
  * Return: int .
 */
int handle_st_dots(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN])
{
	char *parent, *old_cpy = *old_cptr, dir_buff[BUFF_LEN],
	*res = NULL;
	int l_slash_oc, x = -1;

	parent = _strddup(old_cpy), l_slash_oc = last_oc_of(parent, '/');
	parent[l_slash_oc] = '\0';
	if (!_strcmp("..", loc))
	{
		if (!_strcmp("/home", old_cpy))
			free(parent), parent = _strddup("/");
		if (chdir(parent) != 0)
			return (create_error(args, 2));
		*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(parent);
	}
	else
	{
		x = last_spn_oc(is_dot, loc);
		if (x - 1 == 0 && loc[x + 1] == '/')
		{
			res = malloc(_strlen(parent) + _strlen(loc + x + 1) + 1);
			if (!res)
				return (-1);
			res[_strlen(parent) + _strlen(loc + x + 1)] = '\0';
			_strncpy(res, parent, _strlen(parent));
			_strncpy(res + _strlen(parent), loc + x + 1, _strlen(loc + x + 1));
			if (chdir(res) != 0)
				return (create_error(args, 2));
			*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(res);
		}
		else
		{
			res = _strddup(loc);
			if (chdir(res) != 0)
				return (create_error(args, 2));
			*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(res);
		}
		free(parent);
	}
	return (0);
}

/**
  * handle_st_tilds - a function that handles
	* cd arguments starting with tilds
  * @old_cptr: parameter of type char **.
  * @curr_cptr: parameter of type char **.
  * @loc: parameter of type char *.
  * @args: parameter of type char **.
  * @prev: parameter of type char .
  * Return: int .
 */
int handle_st_tilds(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN])
{
	char *parent, *old_cpy = *old_cptr, dir_buff[BUFF_LEN],
	*res = NULL, *home = NULL, *user = _getenv("USER");
	int l_slash_oc, x = -1;

	parent = _strddup(old_cpy), l_slash_oc = last_oc_of(parent, '/');
	home = _strddup("/home/"), parent[l_slash_oc] = '\0';
	if (!_strcmp("~", loc))
	{
		home = _realloc(home, _strlen(home) + 1, _strlen(home) + _strlen(user) + 1);
		_memcpy(user, home + 6, _strlen(user));
		if (chdir(home) != 0)
			return (create_error(args, 2));
		*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(parent), free(home);
	}
	else
	{
		x = last_spn_oc(is_tilde, loc);
		if (x - 1 == -1 && loc[x + 1] == '/')
		{
			res = malloc(_strlen(home) + _strlen(loc + x + 1) + _strlen(user) + 1);
			if (!res)
				return (-1);
			res[_strlen(home) + _strlen(user) + _strlen(loc + x + 1)] = '\0';
			_strncpy(res, home, _strlen(home));
			_strncpy(res + _strlen(home), user, _strlen(user));
			_strncpy(res + _strlen(home) + _strlen(user), loc + x + 1,
			_strlen(loc + x + 1));
			if (chdir(res) != 0)
				return (create_error(args, 2));
			*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(res);
		}
		else
		{
			res = _strddup(loc);
			if (chdir(res) != 0)
				return (create_error(args, 2));
			*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(res);
		}
		free(parent);
	}
	return (0);
}

/**
  * handle_st_hyp - a function that handles
	* cd arguments starting with hyphens
  * @old_cptr: parameter of type char **.
  * @curr_cptr: parameter of type char **.
  * @loc: parameter of type char *.
  * @args: parameter of type char **.
  * @prev: parameter of type char .
  * Return: int .
 */
int handle_st_hyp(char **old_cptr, char **curr_cptr,
	char *loc, char **args, char prev[BUFF_LEN])
{
	char *old_cpy = *old_cptr, dir_buff[BUFF_LEN],
	*curr_cpy = *curr_cptr, *res = NULL, *home = NULL,
	*user = _getenv("USER");
	int l_slash_oc, x = -1;

	x = last_spn_oc(is_hyp, loc);
	if (!prev || !prev[0])
		prev = NULL;
	if (x >= 0 && x <= 1)
	{
		if (loc[x + 1])
			return (create_error(args, 2));
		home = _getenv("HOME");
		if (!home)
			return (-1);
		if (x == 1)
		{
			if (chdir(home) != 0)
				return (create_error(args, 2));
		}
		else
		{
			if (!prev)
			{
				if (chdir(old_cpy) != 0)
					return (create_error(args, 2));
			}
			else
			{
				if (chdir(prev) != 0)
					return (create_error(args, 2));
			}
		}
		*(curr_cptr) = getcwd(dir_buff, sizeof(dir_buff)), free(home);
	}
	else
	{
		return (create_error(args, 2));
	}
	return (0);
}
