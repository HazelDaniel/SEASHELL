#include "main.h"

/**
 * linkpath - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
pathdir_t *linkpath(char *path)
{
	pathdir_t *head = NULL;
	char *token;
	char *cpath = _strddup(path);

	token = _strtok(cpath, ":");
	while (token)
	{
		append_path(token);
		token = _strtok(NULL, ":");
	}
	free(cpath);

	return (head);
}

void append_path(char *value)
{
	pathdir_t* new_path = (pathdir_t *)malloc(sizeof(pathdir_t)), *current;
	char *cpy = _strddup(value), *strip_cpy = rm_tr_slash(cpy);

	if (!new_path)
		return;
	new_path->dir = strip_cpy;
	new_path->next = NULL;

	if (!path_list)
	{
		path_list = new_path;
	}
	else
	{
		current = path_list;
		while (current && current->next != NULL)
			current = current->next;
		current->next = new_path;
	}
	free(cpy);
}

void print_path()
{
	pathdir_t *current = path_list;

	if (!current)
	{
		puts("(nil)");
	}
	while (current)
	{
		printf("current directory:%s\n", current->dir);
		current = current->next;
	}
}
