#include "main.h"

/**
  * norm_dyn_str - the function name
  * @str_ptr: parameter of type char **.
  * Return: void .
 */
void norm_dyn_str(char **str_ptr)
{
	if (*str_ptr && !(*str_ptr)[0])
	{
		free(*str_ptr);
		*str_ptr = NULL;
	}
}

/**
  * _strchr - the function name
  * @str: parameter of type const char *.
  * @c: parameter of type char .
  * Return: char *.
 */
char *_strchr(const char *str, char c)
{
	int f_ind;
	char *f_string;

	f_ind = first_oc_of((char *)str, c);
	if (f_ind < 0)
		return (NULL);
	f_string = (char *)str + f_ind;

	return (f_string);
}

/**
  * _strncpy - the function name
  * @dest: parameter of type char *.
  * @src: parameter of type const char *.
  * @n: parameter of type size_t .
  * Return: char *.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_cpy = dest;

	while (*src && n > 0)
		*dest++ = *src++, n--;

	while (n > 0)
		*dest++ = '\0', n--;

	return (dest_cpy);
}

/**
  * trim_str_arr - the function name
  * @args: parameter of type char **.
  * Return: void .
 */
void trim_str_arr(char **args)
{
	int i, last_nl;
	char *tmp;

	if (!args)
		return;
	for (i = 0; args[i]; i++)
	{
		last_nl = last_oc_of(args[i], '\n');
		tmp = _trim(args[i]);
		if (last_nl + 1 == _strlen(args[i]))
			tmp[last_nl] = '\0';
		free(args[i]);
		args[i] = tmp;
	}
}

/**
  * format_args - the function name
  * @args: parameter of type char **.
  * Return: void .
 */
void format_args(char **args)
{

	int i;
	char *tmp;

	trim_str_arr(args);

	if (!args)
		return;
	for (i = 0; args[i]; i++)
	{
		tmp = _strddup(args[i]);
		free(args[i]);
		args[i] = comment_line(&(tmp));
		free(tmp), tmp = NULL;
	}
	for (i = 0; args[i]; i++)
	{
		if (in_str('$', args[i]))
		{
			tmp = var_replace(args[i]);
			if (tmp)
				free(args[i]), args[i] = tmp;
		}
	}
}
