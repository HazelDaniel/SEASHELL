#include "main.h"

/**
* is_graph - a function that checks if
* a character is graph
* @c: parameter of type char .
* Return: int .
*/
int is_graph(char c)
{
	if (is_print(c) && c != '\t' && c != ' ' && c != '\r' && c != '\n')
		return (1);
	return (0);
}

/**
* is_dot - a function that checks if
* a character is "."
* @c: parameter of type char .
* Return: int .
*/
int is_dot(char c)
{
	return (c == '.');
}

/**
* is_tilde - a function that checks if
* a character is "~"
* @c: parameter of type char .
* Return: int .
*/
int is_tilde(char c)
{
	return (c == '~');
}

/**
* is_hyp - a function that checks if
* a character is "-"
* @c: parameter of type char .
* Return: int .
*/
int is_hyp(char c)
{
	return (c == '-');
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
