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
		int index = 0, k = 0, l_and, l_or, f_and, f_or;

		if (in_str('|', cmd_trim) && in_str('&', cmd_trim))
		{
			f_or = first_oc_of(cmd_trim, '|'), f_and = first_oc_of(cmd_trim, '&');
			l_or = last_oc_of(cmd_trim, '|'), l_and = last_oc_of(cmd_trim, '&');
			/* add more edge cases , not enough. check main.c */
			/* | ... & */
			/* | ... & */
			if (f_and < f_or && l_and > l_or)
				split_by_or_and_order(&c_list, all_c, all_commands[i]);
			else if (f_or < f_and)
				split_by_or_and_order(&c_list, all_c, all_commands[i]);
			else
				split_by_and_or_order(&c_list, all_c, all_commands[i]);
			/* | ... &  .. |*/
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
