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
