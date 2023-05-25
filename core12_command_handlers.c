#include "utils/main.h"

void handle_linked_comms(void);

/**
  * exec_comms - a function that executes the
	* commands in a flow(linked-list)
  * @list: parameter of type const size_t .
  * Return: int .
 */
int exec_comms(const comm_list_t list)
{
	const comm_t *current = list, *curr_head = NULL;
	char **args, *command;
	int (*f)(char **list), i, ret_count = 0;

	while (current != NULL)
	{
		if (current->is_linked)
		{
			curr_head = current->list;
			while (curr_head)
			{
				ret_count = execute(curr_head->command);
				if (ret_count > 0)
					break;
				curr_head = curr_head->next;
			}
		}
		else
		{
			ret_count = execute(current->command);
		}
		if (current->next)
		{
			if (!_strcmp((current->next)->separator, "|") && ret_count == 0)
				break;
			else if (!_strcmp((current->next)->separator, "&") && ret_count > 0)
				break;
		}
		current = current->next;
	}
	return (ret_count);
}

/**
  * eval_comms - a function that checks for nested
	* flows (&&, and || separators basically) and creates
	* another flow list
  * @list: parameter of type const size_t .
  * Return: int .
 */
int eval_comms(const comm_list_t list)
{
	comm_t *current = list;
	char **list_comms, *cmd_list;
	int i;
	comm_list_t link_head = NULL;

	while (current != NULL)
	{
		if (current->is_linked)
		{
			cmd_list = _trim(current->command);
			list_comms = _splitstr(cmd_list, "&");
			if (!list_comms)
				return (-1);
			link_head = NULL;
			for (i = 0; list_comms[i]; i++)
				append_comm(&link_head, '&', list_comms[i], 0);
			current->list = link_head;
		}
		current = current->next;
	}

	return (0);
}

/**
* exec_all_commands - a function that
* executes all commands in a sequence as
* well as in a flow
* description:
* a sequence is ; separated
* a flow is either && or || separated
* Return: void
*/
int exec_all_commands(void)
{
	int i = 0, j = 0, ret_count = 0;
	comm_list_t current = NULL;

	if (!commands)
	{
		return (-1);
	}
	handle_linked_comms();
	for (; commands[i]; i++)
	{
		current = commands[i];
		ret_count += exec_comms(current);
	}
	return (ret_count);
}

/**
* handle_linked_comms - a function that evaluates
* the flow generated and checks if there are even
* more nested flows within
* Return: void
*/
void handle_linked_comms(void)
{
	int i = 0, j = 0, ret_count = 0;
	comm_list_t current = NULL;

	if (!commands)
		return;

	for (; commands[i]; i++)
	{
		current = commands[i];
		ret_count += eval_comms(current);
	}
}
