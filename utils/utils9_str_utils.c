#include "main.h"

/**
  * is_start_str - the function name
  * @strsub: parameter of type char *.
  * @strsup: parameter of type char *.
  * Return: int .
 */
int is_start_str(char *strsub, char *strsup)
{
	int sub_len = _strlen(strsub), sup_len = _strlen(strsup);
	int i;

	if (sub_len > sup_len)
		return (0);

	for (i = 0; i < sub_len ; i++)
	{
		if (strsub[i] != strsup[i])
			break;
	}

	return (i == sub_len);
}

/**
  * is_end_str - the function name
  * @strsub: parameter of type char *.
  * @strsup: parameter of type char *.
  * Return: int .
 */
int is_end_str(char *strsub, char *strsup)
{
	int sub_len = _strlen(strsub), sup_len = _strlen(strsup);
	int i = 0;

	if (sub_len > sup_len)
		return (0);

	if (!sub_len)/* otherwise, sub_len = 0 and i = -1*/
		return (0);

	for (i = sub_len - 1; i >= 0; i--)
	{
		if (strsub[i] != strsup[sup_len - sub_len + i])
			break;
	}
	return (i == -1);
}

/**
  * rm_tr_slash - the function name
  * @str: parameter of type char *.
  * Return: char *.
 */
char *rm_tr_slash(char *str)
{
	int i;
	char *cpy = _strddup(str);

	for (i = 0; str[i]; i++)
		;
	if (str[i - 1] == '/')
		cpy[i - 1] = '\0';
	return (cpy);
}

/**
  * join_list - the function name
  * @list: parameter of type char **.
  * Return: char *.
 */
char *join_list(char **list)
{
	char *acc = NULL;
	int i, j, acc_len = 0, prev_len = 0, next_len = 0;

	if (!list)
		return (NULL);

	for (i = 0; list[i]; i++)
	{
		prev_len = acc_len;
		acc_len += _strlen(list[i]);
		if (!acc)
			acc = _strddup(list[i]);
		else
			acc = _realloc(acc, prev_len + 1, acc_len + 1);
		if (!acc)
			return (acc);
		_memcpy((void *)list[i], (void *)(acc + prev_len), _strlen(list[i]));
	}

	return (acc);
}

/**
  * word_tok - the function name
  * @str: parameter of type char *.
  * Return: char **.
 */
char **word_tok(char *str)
{
	wtok_t *new_tok = NULL;
	char **s_arr, *n_str = NULL, *cpy;
	int i, point, count;

	if (!str)
		return (NULL);
	cpy = _strddup(str), new_tok = gen_tok(cpy);
	if (!new_tok)
	{
		s_arr = malloc(sizeof(char *) + 1);
		if (!s_arr)
			return (NULL);
		s_arr[0] = _strddup(str), s_arr[1] = NULL;
		return (s_arr);
	}
	for (count = 0; new_tok->check_points[count] >= 0; count++)
		;
	s_arr = malloc(sizeof(char *) * (count + 1));
	if (!s_arr)
	{
		free(new_tok);
		return (NULL);
	}
	s_arr[count] = NULL;
	for (i = 0; i < count; i++)
	{
		point = new_tok->check_points[i];
		n_str = malloc(_strlen(cpy + point + 1) + 2);
		if (!n_str)
		{
			free(new_tok), free_str_arr(s_arr, 1);
			return (NULL);
		}
		n_str[_strlen(cpy + point + 1) + 1] = '\0';
		_memcpy((cpy + point + 1), n_str + 1, _strlen(cpy + point + 1));
		n_str[0] = new_tok->vals[i], s_arr[i] = _strddup(n_str), n_str = NULL;
	}
	free(new_tok);

	return (s_arr);
}
