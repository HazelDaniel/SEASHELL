#include "utils/main.h"

int exec_comms(const comm_list_t list)
{
	const comm_t* current = list;
	char **args, *command;
	int (*f)(char **list);

	while (current != NULL)
	{
		args = _splitstr(current->command, " \t");
		trim_str_arr(args);
		command = args[0];
		f = get_builtin(name);
		if (f)
			f(args + 1);
		printf("Command: %s\t Separator: %s\n", current->command, current->separator);
		 if (current->next)
		 	printf("the next guy's separator is : %s\n", (current->next)->separator);
		current = current->next;
	}
	return (0);
}

int exec_all_commands()
{
	int i = 0, j = 0, ret_count = 0;
	comm_list_t current = NULL;

	if (!commands)
	{
		printf("(nil)\n");
		return (-1);
	}
	for (; commands[i]; i++)
	{
		current = commands[i];
		ret_count += exec_comms(current);
	}
	return (ret_count);
}
