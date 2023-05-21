#include "utils/main.h"

int _getAll_env()
{
	int i = 0;

	if (!new_environ)
		return (-1);
	for (; new_environ[i]; i++)
		printf("%s\n", new_environ[i]);
	return (0);
}

char *_getenv(char *input)
{
	int i = 0;
	char *token, *cp_buffer = NULL;

	if (!new_environ)
		return (NULL);
	for (; new_environ[i]; i++)
	{
		cp_buffer = _strddup(new_environ[i]);
		token = _strtok(cp_buffer, "=");
		if (!_strcmp(token, input))
		{
			token = _strtok(NULL, "=");
			empty_state_buff("=");
			return (_strddup(token));
		}
		empty_state_buff("=");
		free(cp_buffer);
		cp_buffer = NULL;
	}
	return (NULL);
}

int _setenv(char *input1, char *input2)
{
	int i = 0, len1 = _strlen(input1), len2 = _strlen(input2),
	index = -1, p_len = _al_len_(new_environ);
	char *new_val = NULL, **tmp_env = new_environ;
	trashenv_t *trash_equiv;

	new_val = malloc((len1 + len2 + 2));
	if (!new_val)
		return (-1);
	_memcpy(input1, new_val, len1), new_val[len1] = '=';
	_memcpy(input2, new_val + len1 + 1, len2);
	new_val[len1 + len2 + 1] = '\0';

	for (i = 0; new_environ[i]; i++)
	{
		if (is_start_str(input1, new_environ[i]))
		{
			free(new_environ[i]);
			new_environ[i] = NULL, new_environ[i] = new_val;
			return (0);
		}
	}
	trash_equiv = pop_trash();
	if (trash_equiv)
	{
		free(new_environ[*(trash_equiv->index)]);
		new_environ[*(trash_equiv->index)] = NULL;
		new_environ[*(trash_equiv->index)] = new_val;
		free(trash_equiv->index), free(trash_equiv->value);
		free(trash_equiv);
		return (0);
	}
	new_environ = (char **)_realloc_ptr(new_environ, p_len, p_len + 1);
	if (!new_environ)
		new_environ = tmp_env;
	else
		new_environ[i] = new_val, new_environ[i + 1] = NULL;

	return (0);
}

void _copyenv()
{
	int count, i;

	free_str_arr(new_environ, 1);
	new_environ = NULL;

	count = _len_p((void **)environ);
	new_environ = malloc((count + 1) * sizeof(char *));
	if (!new_environ)
		return;
	_memcpy_ptr((void **)environ, (void **)new_environ, count);
}

int _unsetenv(char *value)
{
	int count, i;

	for (i = 0; new_environ[i]; i++)
	{
		if (is_start_str(value, new_environ[i]))
		{
			free(new_environ[i]);
			new_environ[i] = _strddup("|=|");
			append_trash(_strddup(value), i);
			break;
		}
	}
	if (new_environ[i])
		return (0);
	else
		return (-1);
}

void _freenv()
{
	free_str_arr(new_environ, 1);
	new_environ = NULL;
}
