#include "utils/main.h"

int handle_exit(char **args)
{
	char *input;

	if (args)
		return (exit_(*args, args));
	else
		return (exit_(NULL, args));
}

int handle_print_env(char **args)
{
	(void)args;

	return (_getAll_env());
}

int handle_set_env(char **args)
{
	int arg_len = _len_p((void *)args);

	if (arg_len != 2)
		return (-1);

	return (_setenv(args[0], args[1]));
}

int handle_unset_env(char **args)
{
	int arg_len = _len_p((void *)args), i;
	int ret_count = 0;

	if (arg_len < 1)
		return (-1);
	if (arg_len > 1)
	{
		for (i = 0; args[i]; i++)
			ret_count += _unsetenv(args[i]);
		if (ret_count == 0)
			return (0);
		else
			return (-1);
	}

	return (_unsetenv(args[0]));
}

int handle_alias(char **args)
{
	int i, ret_count = 0;

	if (!args)
		return alias(NULL);
	for (i = 0; args[i]; i++)
	{
		if (in_str('=', args[i]))
		{
			ret_count += alias(args[i]);
		}
		else
		{
			if (!_getalias(args[i]))
				ret_count--;
		}
	}

	if (ret_count == 0)
		return (0);
	else
		return (-1);
}
