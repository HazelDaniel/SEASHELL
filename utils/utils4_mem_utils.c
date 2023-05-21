#include "main.h"

void **_realloc_ptr(void *ptr, size_t old_size, size_t size)
{
	char **res_tmp = NULL, **ptr_cp;
	void **res = NULL;
	int index = 0;

	if (size == 0 && ptr)
	{
		free_str_arr(ptr, 1);
		return (NULL);
	}
	if (ptr == NULL)
	{
		res = malloc(size * sizeof(void *));
		res_tmp = (char **)res;
		res_tmp[size - 1] = NULL;
	}
	else
	{
		if (size == old_size)
			return (ptr);

		ptr_cp = ptr;
		res = malloc(size * sizeof(void *));
		if (res == NULL)
		{
			free(ptr);
			return (res);
		}
		res_tmp = (char **)res;
		for (index = 0; index < size; index++)
		{
			if (size > old_size && index == old_size)
				break;
			res_tmp[index] = *ptr_cp++;
		}
		--index, res_tmp[index] = NULL;
		free(ptr);
	}
	return (res);
}
/**
 * _realloc - a function that reallocates a memory block
 * @ptr: the address of the old memory block
 * @old_size: the number of elements in the old memory block
 * @size: the number of elements in the new memory block
 * Return: void *
 **/
void *_realloc(void *ptr, size_t old_size, size_t size)
{
	char *res_tmp = NULL, *ptr_cp;
	void *res = NULL;
	int index = 0;

	if (size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		res = malloc(size);
		res_tmp = res;
		res_tmp[size - 1] = '\0';
	}
	else
	{
		if (size == old_size)
			return (ptr);

		ptr_cp = ptr;
		res = malloc(size);
		if (res == NULL)
		{
			free(ptr);
			return (res);
		}
		res_tmp = res;
		for (index = 0; index < size; index++)
		{
			if (size > old_size && index == old_size)
				break;
			res_tmp[index] = *ptr_cp++;
		}
		--index, res_tmp[index] = '\0';
		free(ptr);
	}

	return (res);
}

/**
 * free_str_arr - a function that frees
 * an array of pointers to characters
 * @str_arr: the array in question
 * Return: void
 **/
void free_str_arr(char **str_arr, int is_dyn)
{
	int i = 0;
	if (!str_arr)
		return;
	for (; str_arr[i]; i++)
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
	}
	if (is_dyn)
		free(str_arr);
}

/**
 * _memcpy - copies the content of a pointer
 * into another
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 * Return: void
 */
void _memcpy(void *ptr, const void *newptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
	char_newptr[i] = 0;
}

/**
 * _memcpy_ptr - copies the content of a pointer
 * to pointers into another
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 * Return: void
 */
void _memcpy_ptr(void **ptr, void **newptr, unsigned int size)
{
	char **char_ptr = (char **)ptr;
	char **char_newptr = (char **)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = _strddup((char *)(char_ptr[i]));
	char_newptr[size] = 0;
}
