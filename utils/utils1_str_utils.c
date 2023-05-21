#include "main.h"

/**
	* _strtok - a re-implementation of
	* the strtok function.
	* converts input string to tokens
	* @str: parameter of type char *.
	* @delim: the delimiter
	* description:
	*     extra modification is made to the function
	*     to be able to split commands logically
	*     hence, it may provide results different from the
	*     standard version in some cases
	* Return: char *.
*/
/*YOU ALWAYS WANNA PASS IN TRIMMED STRINGS, SO I PROVIDED A FUNCTION*/
char *_strtok(char *str, char *delim)
{
	static int _index;
	int i = 0, count = 0, rep_count;
	static char *org_buff = NULL;
	ptrdiff_t diff = (ptrdiff_t)str;
	static unsigned long int int_str;

	if (str)
		_index = 0, org_buff = _strddup(str);
	if (!org_buff || !org_buff[0])
		return (NULL);
	if (!str)
	{
		if (_index >= strlen(org_buff))
		{
			free(org_buff), org_buff = NULL;
			return (NULL);
		}
		count = 0, i = 0, diff = (ptrdiff_t)(int_str);
		while (((char *)int_str)[count])
		{
			if (in_str(((char *)int_str)[count], "&|") && in_str(((char *)int_str)[count], delim))
			{
				rep_count = adj_char_num((char *)(int_str + count), ((char *)int_str)[count], _index);
				if (rep_count == 2)
					count += rep_count - 1;
				else
					break;
			}
			else if (in_str(((char *)int_str)[count], delim))
				break;
			i++, count++;
		}
		while (((char *)int_str)[count] && in_str(((char *)int_str)[count], delim))
			((char *)int_str)[count++] = '\0';
		_index += count, int_str += count;
	}
	else
	{
		count = 0, i = 0;
		diff = (ptrdiff_t)(str + count), int_str = (unsigned long int)diff;
		while (str[count])
		{
			if (in_str(str[count], "&|") && in_str(str[count], delim))
			{
				rep_count = adj_char_num((char *)(int_str + count), ((char *)int_str)[count], _index);
				if (rep_count != 2)
					count += rep_count - 1;
				else
					break;
			}
			else if (in_str(str[count], delim))
				break;
			count++, i++;
		}
		while (str[count] && in_str(str[count], delim))
			((char *)int_str)[count++] = '\0';
		_index = count, int_str += count;
	}
	return ((char *)diff);
}

/**
  * _trim - a function that trims
  * @str: the string to trim
  * Return: the trimmed string
 */
char *_trim(char *str)
{
	int pos_start = 0, i = 0, pos_end = strlen(str) - 1,
	stat = 0;
	char *sp_char = " \t", *res = NULL;

	if (!str || !str[0])
		return (NULL);
	while (str[i] != '\0')
	{
		if (!(in_str(str[i], sp_char)))
			break;
		if (stat == 0)
		{
			stat = 1;
			pos_start = i;
			while ((in_str(str[pos_start], sp_char)))
				pos_start++;
		}
		i++;
	}
	i = pos_end;

	for (; i >= 0 && in_str(str[i], sp_char); i--)
		;
	pos_end = i;

	res = (char *)malloc((pos_end - pos_start + 2) * sizeof(char));
	if (res == NULL)
		return (res);
	for (i = 0, stat = pos_start; stat <= pos_end; stat++)
		res[i++] = str[stat];
	res[pos_end - pos_start + 1] = '\0';

	return (res);
}

/**
 * is_print - a function
 * that checks if a character is printable
 * @c: the character parameter
 * Return: int
 **/
int is_print(char c)
{
	return (c >= 33 && c < 127);
}

/**
  * in_str - a function that looks up
	* a character in a string and returns
	* a boolean integer if found
  * @c: parameter of type char .
  * @str: parameter of type char *.
  * Return: int .
 */
int in_str(char c, char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * _strcpy - a function that copies the contents
 * of the source string to the destination string
 * @dest: destination string
 * @src: source string
 * Return: char *
 **/
char *_strcpy(char (*dest)[1024], char **src)
{
	size_t i;

	if (!src || !src[0])
		return (NULL);
	for (i = 0; (*src)[i] != '\0'; i++)
		(*dest)[i] = (*src)[i];
	(*dest)[i] = '\0';
	return ((*dest));
}
