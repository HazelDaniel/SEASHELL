#include "utils/main.h"

char *_trace(char *input)
{
	pathdir_t *current = path_list;
	char *buff = NULL, *res = NULL, *slash = NULL;
	int dir_len, input_len;

	slash = _strddup("/");
	while (current)
	{
		dir_len = _strlen(current->dir), input_len = _strlen(input);
		buff = malloc(dir_len + input_len + 1);
		_memcpy(current->dir, buff, dir_len);
		_memcpy(slash, buff + dir_len, 1);
		_memcpy(input, buff + dir_len + 1, input_len);
		if (access(buff, F_OK) == 0)
		{
			return (buff);
		}
		free(buff);
		buff = NULL;
		current = current->next;
	}
	return (NULL);
}
