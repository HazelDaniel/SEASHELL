#include "utils/main.h"

/**
  * handle_exit - a function that handles
	* the exit commmand
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_exit(char **args)
{
	char *input;

	if (args)
		return (exit_(*args, args));
	else
		return (exit_(NULL, args));
}

/**
  * handle_nothing - a function that handles
	* the '\n' command
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_nothing(char **args)
{
	(void)args;
	return (0);
}

/**
  * handle_print_env - a function that handles
	* the env command
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_print_env(char **args)
{
	(void)args;

	return (getall_env());
}

/**
  * handle_set_env - a function that handles
	* the setenv command
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_set_env(char **args)
{
	int arg_len = _len_p((void *)args);

	if (arg_len != 2)
		return (-1);

	return (_setenv(args[0], args[1]));
}

/**
  * handle_unset_env - a function that handles
	* the unsetenv commmand
  * @args: parameter of type char **.
  * Return: int .
 */
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
