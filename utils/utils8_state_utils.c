#include "main.h"


/**
 * empty_state_buff - a function that
 * empties out and frees the internal
 * static buffer of the strtok function
 * @delim: the delimeter
 * Return: void
 **/
void empty_state_buff(char *delim)
{
	while (_strtok(NULL, delim))
		;
}

/**
 * cleanup - a function that frees up all the
 * major resources created to start a process
 * Return: void
 **/
void cleanup(void)
{
	_freenv();
	free_path();
	free_aliases(aliases);
	free_vars(variables);
	free_commands();
}
