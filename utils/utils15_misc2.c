#include "main.h"


int dig_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
		len++, num1 = num * -1;
	else
		num1 = num;

	while (num1 >= 10)
		len++, num1 /= 10;

	return (len);
}

char *_itoa(int num)
{
	char *buffer;
	int len = dig_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
		num1 = num * -1, buffer[0] = '-';
	else
		num1 = num;

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

wtok_t *gen_tok(char *str)
{
	int i = 0, count = 0;
	wtok_t *new_tok = NULL;
	int s_len = _strlen(str);

	if (!str)
		return (NULL);

	new_tok = (wtok_t *)malloc(sizeof(wtok_t));
	if (!new_tok)
		return (NULL);

	if (!(is_hwp(str[0])))
	{
		new_tok->vals[count] = str[0];
		new_tok->check_points[count] = 0;
		str[0] = '\0';
		i++, count++;
	}
	for (; str[i]; i++)
	{
		if (is_hwp(str[i]) && is_print(str[i + 1]) && str[i + 1])
		{
			new_tok->vals[count] = str[i];
			new_tok->check_points[count] = i;
			str[i] = '\0';
			count++;
		}
	}

	new_tok->check_points[count] = -1;
	if (!count)
	{
		free(new_tok);
		return (NULL);
	}
	return (new_tok);
}

char *comment_line(char **buff_ptr)
{
	char *cpy = NULL;
	int hash_oc;

	if (!buff_ptr)
		return (NULL);
	cpy = _strddup(*buff_ptr);
	hash_oc = first_oc_of(cpy, '#');
	if (hash_oc >= 0)
	{
		if (hash_oc > 0 && cpy[hash_oc - 1] == '\\')
			;
		else
			cpy[hash_oc] = '\0', norm_dyn_str(&cpy);
	}

	return (cpy);
}

void norm_dyn_str(char **str_ptr)
{
	if (*str_ptr && !(*str_ptr)[0])
	{
		free(*str_ptr);
		*str_ptr = NULL;
	}
}

char * _strchr(const char *str, char c)
{
	int f_ind;
	char *f_string;

	f_ind = first_oc_of((char *)str, c);
	if (f_ind < 0)
		return (NULL);
	else
		f_string = (char *)str + f_ind;

	return (f_string);
}

char* _strncpy(char* dest, const char* src, size_t n)
{
	char* dest_cpy = dest;

	while (*src && n > 0)
		*dest++ = *src++, n--;

	while (n > 0)
		*dest++ = '\0', n--;

	return (dest_cpy);
}

void trim_str_arr(char **args)
{
	int i;
	char *tmp;

	if (!args)
		return;
	for (i = 0; args[i]; i++)
	{
		tmp = _trim(args[i]);
		free(args[i]);
		args[i] = tmp;
	}
}
