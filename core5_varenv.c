#include "utils/main.h"

static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr);
char *eval_n_expand(char **str_p);

/**
 * _getall_vars - a function that retrieves
 * all the environment variables
 * Return: void
 **/
void _getall_vars(void)
{
	int i = 0;
	var_t *current = variables;

	if (!current)
		puts("(nil)");

	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

/**
 * _getvar - a function that retrieves
 * a shell variable
 * @input: the input string
 * Return: char *
 **/
char *_getvar(char *input)
{
	int i = 0;
	char *token, *cp_buffer = NULL, *tok_cpy = NULL;
	var_t *current = variables;

	if (!current || !input || !is_start_str("$", input))
		return (NULL);
	while (current)
	{
		if (is_start_str(input + 1, current->value))
		{
			cp_buffer = _strddup(current->value);
			(void)_strtok(cp_buffer, "=");
			token = _strtok(NULL, "=");
			tok_cpy = _strddup(token);
			empty_state_buff("=");
			free(cp_buffer), cp_buffer = NULL;
			return (tok_cpy);
		}
		current = current->next;
	}

	return (NULL);
}

/**
 * _setvar - a function that sets
 * a shell variable
 * @input: the input string
 * Return: char *
 **/
char *_setvar(char *input)
{
	var_t *current = variables, *new_var, *prev;
	char *cpy = NULL, *key = NULL;

	if (is_start_str("$", input) &&
		!(is_start_str("$=", input)) &&
		!(is_start_str("?=", input)))
	{
		return (NULL);
	}

	new_var = (var_t *)malloc(sizeof(var_t));
	if (!new_var)
		return (NULL);
	new_var->value = _strddup(input), new_var->next = NULL;
	if (!variables)
	{
		variables = new_var;
		return (new_var->value);
	}
	cpy = _strddup(input), key = _strtok(cpy, "=");
	empty_state_buff("="), current = variables;

	if (!current->next)
	{
		if (compare_and_sub(&current,
		&new_var, &input, &cpy, &key))
			return (current->value);
		current->next = new_var;
		return (new_var->value);
	}
	while (current && current->next)
	{
		if (compare_and_sub(&current,
		&new_var, &input, &cpy, &key))
			return (current->value);
		current = current->next;
	}
	if (compare_and_sub(&current,
	&new_var, &input, &cpy, &key))
		return (current->value);
	current->next = new_var;
	free(cpy);

	return (new_var->value);
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
static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
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

/**
  * free_vars - a function that frees
	* the shell variables
  * @list: parameter of type char var_t *
  * Return: void
 */
void free_vars(var_t *list)
{
	var_t *current = list, *next = NULL;

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
  * lookup_var - a function that does
	* a lookup of any variable in both the shell
	* and the environment
  * @input: parameter of type char *.
  * Return: char *.
 */
char *lookup_var(char *input)
{
	char *buff = NULL;

	if (!is_start_str("$", input))
		return (NULL);

	buff = _getvar(input);
	if (!buff)
		buff = _getenv(input + 1);

	return (buff);
}

/**
  * var_replace - a function that does
	* a variable expansion on input strings
  * @string: the input string
  * Return: char *.
 */
char *var_replace(const char *string)
{
	const char *var_pat =
		"$_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789?$";
	size_t string_length = _strlen((char *)string), env_var_length;
	char *result = NULL, var_name[MVL], *env_var, *name_cpy;
	size_t result_index = 0, j, var_len, i;

	result = malloc(sizeof(char) *(string_length + 1));
	if (!result)
		return (NULL);
	for (i = 0; i < string_length; ++i)
	{
		if (string[i] == '$')
		{
			j = i + 1, var_len = 0;
			while (_strchr(var_pat, string[j]) && var_len < MVL - 1 && j < string_length)
				var_name[var_len++] = string[j++];
			var_name[var_len] = '\0', name_cpy = malloc(_strlen(var_name) + 2);
			if (!name_cpy)
				return (NULL);
			name_cpy[0] = '$', _memcpy(var_name, name_cpy + 1, _strlen(var_name));
			name_cpy[_strlen(var_name) + 1] = '\0';
			if (var_len > 0)
			{
				env_var = lookup_var(name_cpy);
				if (env_var != NULL)
				{
					env_var_length = _strlen(env_var);
					result = _realloc(result, _strlen(result) + 1, _strlen(result)
					 + 1 + _strlen(env_var));
					_memcpy(env_var, result + result_index, _strlen(env_var));
					result_index += env_var_length, i += var_len;
					continue;
				}
			}
		}
		result[result_index++] = string[i];
	}
	result[result_index] = '\0';

	return (_strlen(result) == 1 && !*result ? NULL : result);
}
