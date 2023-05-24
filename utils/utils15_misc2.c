#include "main.h"

/**
  * last_spn_oc - a function that returns the
	* last spanning occurrence a character in a string
	* based on some properties starting at the first index
  * @f: the property as a function
  * @str:  the string
  * Return: int .
 */
int last_spn_oc(int (*f)(char c), char *str)
{
	int count = 0;

	if (!str)
		return (-1);
	while (str[count] && f(str[count]))
		count++;
	count--;

	return (count);
}

/**
  * dig_len - a function that returns
	* the number of digits an integer has
  * @num: parameter of type int .
  * Return: int .
 */
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

/**
  * _itoa - a function taht converts integer
	* to string
  * @num: parameter of type int .
  * Return: char *.
 */
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

/**
 * gen_tok - a function that generates a word token from
 * a string
 * @str: the string
 * Return: wtok_t *
 **/
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

/**
  * comment_line - a function that terminates
	* a string at an index containing the # character
  * @buff_ptr: parameter of type char **.
  * Return: char *.
 */
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
