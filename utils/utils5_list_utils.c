#include "main.h"

/**
  * append_comm - a function that appends a new
	* command to the end of the command flow
  * @list: parameter of type comm_list_t *.
  * @separator: parameter of type char .
  * @command: parameter of type const char *.
  * @status: parameter of type int .
  * Return: void .
 */
void append_comm(comm_list_t *list, char separator,
	const char *command, int status)
{
	comm_t *new_comm = (comm_t *)malloc(sizeof(comm_t)), *current;
	static int id;

	if (!new_comm)
		return;
	new_comm->separator = _strddup((char *)&separator);
	new_comm->separator[1] = '\0';
	new_comm->command = _strddup((char *)command);
	new_comm->status = (int *)malloc(sizeof(int));
	new_comm->id = id++;
	*(new_comm->status) = status;
	new_comm->next = NULL;

	if (in_str('&', new_comm->command))
		new_comm->is_linked = 1;
	else
		new_comm->is_linked = 0;

	if (!*list)
	{
		*list = new_comm;
	}
	else
	{
		current = *list;

		while (current && current->next)
			current = current->next;
		current->next = new_comm;
	}
}

/**
  * prepend_comm - a function that prepends a new
	* command to the end of the command flow
  * @list: parameter of type comm_list_t *.
  * @separator: parameter of type char .
  * @command: parameter of type const char *.
  * @status: parameter of type int .
  * Return: void .
 */
comm_t *prepend_comm(comm_list_t *list, char separator,
	const char *command, int status)
{
	comm_t *new_comm = (comm_t *)malloc(sizeof(comm_t)), *current;
	static int id;

	if (!new_comm)
		return (NULL);
	new_comm->separator = _strddup((char *)&separator);
	new_comm->separator[1] = '\0';
	new_comm->command = _strddup((char *)command);
	new_comm->status = (int *)malloc(sizeof(int));
	new_comm->id = id++;
	*(new_comm->status) = status;
	new_comm->next = NULL;

	if (!*list)
	{
		*list = new_comm;
	}
	else
	{
		current = new_comm;
		current->next = *list;
		*list = current;
	}
	return (*list);
}

/**
  * append_comm_list - a function that prepends a new
	* command flow to the end of the command order
  * @list: parameter of type comm_list_t.
  * Return: void .
 */
void append_comm_list(comm_list_t list)
{
	comm_list_t *tmp = commands;
	int p_len;
	static int index;

	if (!commands)
		commands = (comm_list_t *)malloc(sizeof(comm_list_t *)), index = 0;
	if (!commands)
		return;
	commands[index++] = list;
	p_len = _al_len_(commands) * sizeof(comm_list_t);
	commands = _realloc(commands, p_len, p_len + sizeof(comm_list_t));
	if (!commands)
		commands = tmp;
	else
		commands[index] = NULL;
}

/**
  * print_comms - a function that prints
	* all commands in a command flow
  * @list: parameter of type comm_list_t.
  * Return: void .
 */
void print_comms(const comm_list_t list)
{
	const comm_t *current = list;

	puts("----------------------->");
	while (current)
	{
		printf("Command: %s\t Separator: %s\n",
		current->command, current->separator);
		if (current->next)
		{
			printf("the previous guy's separator is : %s\n",
			(current->next)->separator);
		}
		current = current->next;
	}
}

/**
  * print_comms_full - a function that prints
	* all commands
  * Return: void .
 */
void print_comms_full(void)
{
	int i = 0, j = 0;
	comm_list_t current = NULL;

	if (!commands)
	{
		printf("(nil)\n");
		return;
	}
	for (; commands[i]; i++)
	{
		current = commands[i];
		print_comms(current);
		puts("======================>");
	}
}

/**
  * clear_comms - a function that clears
	* all commands
	* @list: a parameter of type comm_list_t
  * Return: void .
 */
void clear_comms(comm_list_t list)
{
	comm_list_t current = list, next = NULL;

	if (!current)
		return;
	while (current)
	{
		if (current->next == NULL)
		{
			free(current->status);
			free(current->command);
			free(current->separator);
			free(current);
			current = NULL;
			return;
		}
		next = current->next;
		if (current->is_linked)
			clear_comms(current->list);
		free(current->status);
		free(current->command);
		free(current->separator);
		free(current);
		current = next;
	}
}

/**
  * free_commands - a function that frees
	* all commands
  * Return: void .
 */
void free_commands(void)
{
	int i = 0, j = 0;

	if (!commands)
		return;

	for (i = 0; commands[i]; i++)
	{
		clear_comms(commands[i]);
	}
	free(commands);
	commands = NULL;
}

/**
  * remove_command - a function that removes
	* a command from a command flow
	* @list: parameter of type comm_t *
	* @value: the id of the command
  * Return: void .
 */
void remove_command(comm_t *list, int value)
{
	comm_t *current = list, *prev = NULL;

	if (!current)
		return;
	while (current && (current->id != value))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (!prev)
			list = current->next;
		else
			prev->next = current->next;
		free(current->command);
		free(current->status);
		free(current);
		current = NULL;
	}
}
