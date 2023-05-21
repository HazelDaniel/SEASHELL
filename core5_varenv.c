#include "utils/main.h"

static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr);
void norm_dyn_str(char **str_ptr);

void _getall_vars()
{
	int i = 0;
	var_t *current = variables;

	if (!current)
		puts("(nil)");

	while(current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

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

char *_setvar(char *input)
{
	var_t *current = variables, *new_var, *prev;
	char *cpy = NULL, *key = NULL;

	if (is_start_str("$", input) &&
		!(is_start_str("$=", input)))
	{
		return (NULL);
	}

	new_var = (var_t *)malloc(sizeof(var_t));
	if (!new_var)
		return (NULL);
	new_var->value = _strddup(input);
	new_var->next = NULL;
	if (!variables)
	{
		variables = new_var;
		return (new_var->value);
	}
	cpy = _strddup(input), key = _strtok(cpy, "=");
	empty_state_buff("=");
	current = variables;

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

char *expand(char *input)
{
	char **splitted = NULL, *match, *query,
	*res = NULL, *res_match, *patch = NULL, *pre_patch = NULL;
	int i, ind = -1, l_word = -1, res_len;

	splitted = word_tok(input);
	if (!splitted)
		return (NULL);
	for (i = 0; splitted[i]; i++)
	{
		if (!in_str('$', splitted[i]))
			continue;
		ind = first_oc_of(splitted[i], '$');
		l_word = last_oc(is_word, splitted[i]);
		pre_patch = _strddup(splitted[i]);
		if (l_word >= 0)
			patch = _strddup(splitted[i] + l_word + 1);
		else
			patch = NULL;
		pre_patch[ind] = '\0';
		norm_dyn_str(&patch), norm_dyn_str(&pre_patch);
		query = _strddup(splitted[i] + _strlen(pre_patch));
		l_word = last_oc(is_word, query);
		query[l_word + 1] = '\0';
		if (splitted[i][ind] == splitted[i][ind + 1])
			query = _strddup("$$");
		if (splitted[i][ind + 1] == '?')
			query = _strddup("$?");
		match = lookup_var(query);
		norm_dyn_str(&query);
		if (!query || !match)
		{
			if (!query)
				match = _strddup("$");
			free(pre_patch), free(match), free(patch), free(query);
			continue;
		}
		res_len = _strlen(pre_patch) + _strlen(match) + _strlen(patch);
		res_match = malloc(res_len + 1);
		if (!res_match)
			return (NULL);
		res_match[res_len] = '\0';
		_memcpy(pre_patch, res_match, _strlen(pre_patch));
		_memcpy(match, res_match + _strlen(pre_patch), _strlen(match));
		_memcpy(patch, res_match + _strlen(pre_patch)
			+ _strlen(match), _strlen(patch)), free(splitted[i]),
		free(query), free(pre_patch), free(match); free(patch);
		splitted[i] = res_match;
	}
	res = (join_list(splitted)), free_str_arr(splitted, 1);
	return (res);
}

void norm_dyn_str(char **str_ptr)
{
	if (*str_ptr && !(*str_ptr)[0])
	{
		free(*str_ptr);
		*str_ptr = NULL;
	}
}
