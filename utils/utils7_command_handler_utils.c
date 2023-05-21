#include "main.h"

int parse_to_commands(char *string)
{
	char **all_commands = NULL, *cmd_list = _trim(string);
	all_commands = _splitstr(cmd_list, ";");
	if (!all_commands)
		return (-1);
	handle_parsed_commands(all_commands);
	free(cmd_list);

	return (0);
}

void handle_parsed_commands(char **all_commands)
{
	int i;

	for (i = 0; all_commands[i]; i++)
	{
		char *cmd_trim = _trim(all_commands[i]), *sub_cmd_trim = NULL;
		char **all_c = NULL;
		comm_list_t c_list = NULL;
		int index = 0, k = 0;

		if (in_str('|', cmd_trim) && in_str('&', cmd_trim))
		{
			if (first_oc_of(cmd_trim, '|') < first_oc_of(cmd_trim, '&'))
				split_by_or_and_order(&c_list, all_c, all_commands[i]);
			else
				split_by_and_or_order(&c_list, all_c, all_commands[i]);
		}
		else if (in_str('|', cmd_trim))
		{
			split_by_or(&c_list, all_c, all_commands[i]);
		}
		else if (in_str('&', cmd_trim))
		{
			split_by_and(&c_list, all_c, all_commands[i]);
		}
		else
		{
			append_comm(&c_list, '\0', all_commands[i], 0);
		}
		append_comm_list(c_list, &comms_index);
		free(cmd_trim);
	}
}
