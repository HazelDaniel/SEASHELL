#include "utils/main.h"

static int compare_and_sub(var_t **current_ptr, var_t **new_ptr,
	char **input_ptr, char **cpy_ptr, char **key_ptr);
char *eval_n_expand(char **str_p);

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
	int i, ind = -1, ind2 = -1, l_word = -1, res_len;

	splitted = word_tok(input);
	if (!splitted)
		return (NULL);
	for (i = 0; splitted[i]; i++)
	{
		if (!in_str('$', splitted[i]))
			continue;
		ind = first_oc_of(splitted[i], '$');
		ind2 = last_oc_of(splitted[i], '$');
		if (ind2 > ind + 1)
			continue;
		l_word = last_spn_oc(is_word, splitted[i] + ind + 1);
		l_word += ind + 1;
		pre_patch = _strddup(splitted[i]);
		if (l_word != ind)
			patch = _strddup(splitted[i] + l_word + 1);
		else
			patch = NULL;
		pre_patch[ind] = '\0';
		norm_dyn_str(&patch), norm_dyn_str(&pre_patch);
		query = _strddup(splitted[i] + _strlen(pre_patch));
		l_word = last_spn_oc(is_word, query + 1);
		query[l_word + 2] = '\0';
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

char* var_replace(const char* string)
{
	const char* var_pat = "$_ABCDEFGHIJKLMNOP\
		QRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	size_t string_length = _strlen((char *)string), env_var_length;
	char* result = NULL, var_name[MVL], *env_var, *name_cpy;
	size_t result_index = 0, j, var_len, i;

	result = malloc((string_length + 1));
	if (!result)
		return (NULL);
	for (i = 0; i < string_length; ++i)
	{
		if (string[i] == '$')
		{
			j = i + 1, var_len = 0;
			while (_strchr(var_pat, string[j]) && var_len < MVL - 1)
				var_name[var_len++] = string[j++];
			var_name[var_len] = '\0'; name_cpy = malloc(_strlen(var_name) + 2);
			if(!name_cpy)
				return (NULL);
			name_cpy[0] = '$';
			_memcpy(var_name, name_cpy + 1, _strlen(var_name));
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

	return (result);
}
