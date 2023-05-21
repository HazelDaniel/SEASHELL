#include "main.h"

char **_splitstr(char *str, char *delim)
{
	char **res_str = NULL, *token, cp_buff[1024] = "", *res_buff[1024] = {NULL},
	*trimmed = _trim(str);
	size_t count = 0, res_index = 0, i = 0;

	if (!trimmed)
		return (NULL);
	token = _strtok(__cp__(cp_buff, trimmed), delim);
	while (token)
	{
		count = 0;
		while (token[count])
			count++;
		res_buff[res_index] = malloc((count + 1) * sizeof(char));
		if (!res_buff[res_index])
		{
			for (i = 0; i < res_index; i++)
				free(res_buff[i]), free(trimmed);
			return (NULL);
		}
		res_buff[res_index][count] = '\0';
		for (i = 0; token[i]; i++)
			res_buff[res_index][i] = token[i];
		token = _strtok(NULL, delim);
		res_index++;
	}
	res_str = malloc((res_index + 1) * sizeof(char *));
	if (res_str == NULL)
	{
		free_str_arr(res_buff, 1), free(trimmed);
		return (NULL);
	}
	res_str[res_index] = NULL;
	for (i = 0; i < res_index; i++)
		res_str[i] = res_buff[i];
	free(trimmed);

	return (res_str);
}

/**
 * _strddup - a function that returns a duplicate, dynamically
 * allocated array of characters
 * @src: the source string
 * Return: the duplicated string
 **/
char *_strddup(char *src)
{
	int i = 0, len = _strlen(src);
	char *res = NULL;

	if (!src)
		return (NULL);
	res = malloc((len + 1));
	if (!res)
		return (res);
	res[len] = '\0';

	for (; src[i]; i++)
		res[i] = src[i];

	return (res);
}

/**
 * adj_char_num - a function that returns
 * the number of repeating characters in
 * a string starting at the index of the first
 * repeating character
 * @str: the string
 * @c: the repeating character
 * @i: the index
 * Return: int
 **/
int adj_char_num(char *str, char c, int i)
{
	int tmp = i, count = 0;

	(void)i;
	while (str[tmp] && str[tmp] == c)
		count++, tmp++;
	
	return (count);
}

/**
 * first_oc_of - a function that returns
 * the first occurrence of a character
 * in a string
 * @str: the string
 * @c: the character
 * Return: int
 **/
int first_oc_of(char *str, char c)
{
	int count = 0;

	while (str[count] && str[count] != c)
		count++;

	if (str[count] == c)
		return (count);
	else
		return (-1);
}

int first_oc(int (* f)(char c), char *str)
{
	int count = 0;

	while (str[count] && !f(str[count]))
		count++;

	if (f(str[count]))
		return (count);
	else
		return (-1);
}
/**
 * _strlen_p - returns the length of an array of
 * derived objects
 * @p: array of derived objects
 * Return: int
 **/
int _len_p(void **p)
{
	int i = 0;

	for (; p[i]; i++)
		;
	return (i);
}
