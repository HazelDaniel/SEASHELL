#include "utils/main.h"

int exec_comms(const comm_list_t list)
{
	const comm_t *current = list, *prev;
	char **args, *command;
	int (*f)(char **list), i;

	while (current != NULL)
	{
		args = _splitstr(current->command, " \t");
		trim_str_arr(args);
		command = args[0];
		f = get_builtin(command);
		if (f)
		{
			f(args + 1);
		}
		else
		{
			printf("unknown command :%s\n", command);
		}
		// printf("Command: %s\t Separator: %s\n", current->command, current->separator);
		 if (current->next)
		 	printf("the next guy's separator is : %s\n", (current->next)->separator);
		prev = current;
		current = current->next;
		// remove_command((comm_t *)prev, prev->id);
	}
	return (0);
}

int exec_all_commands()
{
	int i = 0, j = 0, ret_count = 0;
	comm_list_t current = NULL;

	if (!commands)
	{
		return (-1);
	}
	for (; commands[i]; i++)
	{
		printf("what in the heck is wrong\n");
		current = commands[i];
		// ret_count += exec_comms(current);
	}
	free_commands();
	return (ret_count);
}
