#include "utils/main.h"

/**
  * handle_cd - a function that handles
	* a cd command
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_cd(char **args)
{
	char *input;

	if (!args)
		input = NULL;
	else
		input = *args;

	if (cd(input, args) == 0)
		return (0);

	return (-1);
}

/**
  * handle_help - a function that handles
	* a help command
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_help(char **args)
{
	char *input;

	if (!args)
		input = NULL;
	else
		input = *args;

	if (help(input) == 0)
		return (0);

	return (-1);
}

/**
  * handle_alias - a function that handles
	* the alias commmand
  * @args: parameter of type char **.
  * Return: int .
 */
int handle_alias(char **args)
{
	int i, ret_count = 0;

	if (_len_p((void *)args) == 1 && last_oc(is_word, *args) < 0)
		free(*args), *args = NULL;
	if (!args || !args[0])
		return (alias(NULL));
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
