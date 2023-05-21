#include "main.h"

/**
  * _strcmp - a function that compares two strings
  * @str1_ptr: parameter of type char **
  * @str2_ptr: parameter of type char **
  * Return: an integer value
	* description: 0 if str1 == str2
	*              len(str1) - len(str2) if str1 != str2
	* warning: don't pass in the address of a null pointer
	*  you'll get the same behavior as the standard strcmp
	*  function
 */
int _strcmp(char *str1, char *str2)
{
	int count, i, len1 = _strlen(str1), len2 = _strlen(str2);

	if (!str1 && !str2)
		return (0);
	if (!str1 && str2)
		return (len2);
	if (str1 && !str2)
		return (len1);
	count = 0;
	if (str1[count] != str2[count])
		return (len1 + len2);

	while (str1[count] == str2[count] && (str2[count] && str1[count]))
		count++;
	if (!str1[count] && !str2[count])
		return (0);
	if (str1[count] && str2[count])
		return (find_max(len1, len2) - count);
	i = 0;
	if (str1[count] && !str2[count])
	{
		while (str1[count])
			count++, i++;
		return (i);
	}
	if (!str1[count] && str2[count])
	{
		while (str2[count])
			count++, i++;
		return (-i);
	}
	return (count);/* not needed all paths handled already */
}

/**
 * _strlen - a function that computes
 * the lenght of a string
 * @str: the string
 * Return: unsigned int
 **/
unsigned int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (len);
	while (str[len])
		len++;

	return (len);
}

/**
* _strcat - A function that concatenates two strings
* @dest: a destination string
* @src: a string to append
* Return: Always a string
**/
char *_strcat(char *dest, char *src)
{
	int dest_count = 0;
	int src_count = 0;

	if (!dest)
		return (NULL);
	if (!src)
		return (dest);

	while (dest[dest_count] != '\0')
	{
		dest_count++;
	}

	while (src[src_count] != '\0')
	{
		dest[dest_count] = src[src_count];
		src_count++;
		dest_count++;
	}
	dest[dest_count] = '\0';
	return (dest);
}

/**
* _strdcat - A function that concatenates two strings
* dynamically
* @dest: a destination string
* @src: a string to append
* description: the first string and only that needs to be
*     dynamically allocated
* Return: Always a string
**/
char *_strdcat(char *dest, char *src)
{
	int dest_count = 0, src_count = 0, ind = 0;
	unsigned int res_len = 0, len_dest = _strlen(dest);
	char *res = NULL;

	res_len = _strlen(src) + len_dest;

	res = malloc((res_len + 1) * sizeof(char));
	if (res == NULL)
		return (res);
	if (res_len == 0)
		return (NULL);
	res[res_len] = '\0';

	for (ind = 0; ind < len_dest; ind++)
		res[ind] = dest[ind];
	for (; ind < res_len; ind++)
		res[ind] = src[ind];
	free(dest);

	return (res);
}
