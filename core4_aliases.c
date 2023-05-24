#include "utils/main.h"

static int compare_and_sub(alias_t **current_ptr, alias_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr);

/**
  * alias - a function that exposes the core
	* functionality of the alias command
  * @input: parameter of type char *.
  * Return: int .
 */
int alias(char *input)
{
	if (!input)
	{
		print_aliases();
		return (0);
	}
	if (in_str('=', input))
	{
		if (_setalias(input))
			return (0);
		return (-1);
	}
	return (-1);
}

/**
  * _getalias - a function that retrieves
	* an alias from an input string
  * @input: parameter of type char *.
  * Return: char *.
 */
char *_getalias(char *input)
{
	int i = 0;
	char *token, *cp_buffer = NULL;
	alias_t *current = aliases;

	while (current)
	{
		if (is_start_str(input, current->value))
		{
			printf("%s\n", current->value);
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

/**
  * _setalias - a function that sets
	* an alias given an input string
  * @input: parameter of type char *.
  * Return: char *.
 */
char *_setalias(char *input)
{
	alias_t *new_alias, *current;
	char *cpy = NULL, *key = NULL;

	new_alias = (alias_t *)malloc(sizeof(alias_t));
	if (!new_alias)
		return (NULL);
	new_alias->value = _strddup(input), new_alias->next = NULL;

	if (!aliases)
	{
		aliases = new_alias;
		return (new_alias->value);
	}
	cpy = _strddup(input), key = _strtok(cpy, "=");
	empty_state_buff("=");
	current = aliases;

	if (!current->next)
	{
		if (compare_and_sub(&current,
		&new_alias, &input, &cpy, &key))
			return (current->value);
		current->next = new_alias;
		return (new_alias->value);
	}
	while (current && current->next)
	{
		if (compare_and_sub(&current,
		&new_alias, &input, &cpy, &key))
			return (current->value);
		current = current->next;
	}
	if (compare_and_sub(&current,
	&new_alias, &input, &cpy, &key))
		return (current->value);
	current->next = new_alias;
	free(cpy);

	return (new_alias->value);
}

/**
  * free_aliases - a function that
	* frees up all the aliases defined
  * @list: parameter of type alias_t *
  * Return: void
 */
void free_aliases(alias_t *list)
{
	alias_t *current = list, *next = NULL;

	if (!current)
		return;
	while (current)
	{
		if (current->next == NULL)
		{
			free(current->value);
			free(current);
			current = NULL;
			return;
		}
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	list = NULL;
}

/**
  * print_aliases - a function that prints all aliases
  * Return: void .
 */
void print_aliases(void)
{
	alias_t *current = aliases, *next = NULL;

	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

/**
  * compare_and_sub - a utility function
	* for checking the existence of an alias
	* in the alias table
  * @current_ptr: parameter of type alias_t **
  * @new_ptr: parameter of type alias_t **
  * @input_ptr: parameter of type char **
  * @cpy_ptr: parameter of type char **
  * @key_ptr: parameter of type char **
  * Return: int
 */
static int compare_and_sub(alias_t **current_ptr, alias_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr)
{
	if (!_strcmp(((*current_ptr)->value), *input_ptr))
	{
		free((*new_ptr)->value), free(*cpy_ptr), free(*new_ptr);
		return (1);
	}
	else if (is_start_str(*key_ptr, (*current_ptr)->value))
	{
		free((*new_ptr)->value), free((*current_ptr)->value),
		free(*cpy_ptr);
		(*current_ptr)->value = _strddup(*input_ptr);
		return (1);
	}

	return (0);
}
