#include "main.h"


/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_memcpy(name, error, _strlen(name));
	_memcpy(": ", error + _strlen(name), 2);
	_memcpy(hist_str, error + _strlen(name) + 2, _strlen(hist_str));
	_memcpy(": ", error + _strlen(name) + 2 + _strlen(hist_str), 2);
	_memcpy(args[0], error + _strlen(name)
	 + 2 + _strlen(hist_str) + 2, _strlen(args[0]));
	_memcpy(": not found\n", error + _strlen(name) + 2
	 + _strlen(hist_str) + 2 + _strlen(args[0]), 12);

	free(hist_str);
	return (error);
}
