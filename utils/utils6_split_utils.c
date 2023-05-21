#include "main.h"

/**
  * split_by_or - a function that splits
	* a string by || logical separators
  * @c_list: parameter of type comm_list_t *.
  * @raw_token: parameter of type char **.
  * @curr_token: parameter of type char *.
  * Return: void .
 */
void split_by_or(comm_list_t *c_list,
	char **raw_token, char *curr_token)
{
	int j;
	char *cmd_trim = _trim(curr_token);

	raw_token = _splitstr(cmd_trim, "|");
	for (j = 0; raw_token[j]; j++)
		append_comm(c_list, '|', raw_token[j], 0);
	
	free(raw_token);
	free(cmd_trim);
}

/**
  * split_by_and - a function that splits a string
	* by && logical separators
  * @c_list: parameter of type comm_list_t *.
  * @raw_token: parameter of type char **.
  * @curr_token: parameter of type char *.
  * Return: void .
 */
void split_by_and(comm_list_t *c_list,
	char **raw_token, char *curr_token)
{
	int j;
	char *cmd_trim = _trim(curr_token);

	raw_token = _splitstr(cmd_trim, "&");
	for (j = 0; raw_token[j]; j++)
		append_comm(c_list, '&', raw_token[j], 0);
	
	free(raw_token);
	free(cmd_trim);
}

/**
  * split_by_and_or_order - a function that splits
	* a string containing both logical operators
	* || and && by order of precedence
  * @c_list: parameter of type comm_list_t *.
  * @raw_token: parameter of type char **.
  * @curr_token: parameter of type char *.
  * Return: void .
 */
void split_by_and_or_order(comm_list_t *c_list,
	char **raw_token, char *curr_token)
{
	int j;
	char *cmd_trim = _trim(curr_token), **raw_sub_token = NULL;

	raw_token = _splitstr(cmd_trim, "|");
	/* split by and */
	for (j = 0; raw_token[j]; j++)
	{
		if (in_str('&', raw_token[j]))
			split_by_and(c_list, raw_sub_token, raw_token[j]);
	}
	/* split by or exclusively */
	for (j = 0; raw_token[j]; j++)
	{
		if (!in_str('&', raw_token[j]))
			append_comm(c_list, '|', raw_token[j], 0);
	}

	free(raw_token);
	free(cmd_trim);
}


/**
  * split_by_or_and_order - a function that splits
	* a string containing both logical operators
	* || and && by order of precedence
  * @c_list: parameter of type comm_list_t *.
  * @raw_token: parameter of type char **.
  * @curr_token: parameter of type char *.
  * Return: void .
 */
void split_by_or_and_order(comm_list_t *c_list,
	char **raw_token, char *curr_token)
{
	int j;
	char *cmd_trim = _trim(curr_token), **raw_sub_token = NULL;

	raw_token = _splitstr(cmd_trim, "|");
	/* split by or exclusively */
	for (j = 0; raw_token[j]; j++)
	{
		if (!in_str('&', raw_token[j]))
			append_comm(c_list, '|', raw_token[j], 0);
	}

	/* split by and */
	for (j = 0; raw_token[j]; j++)
	{
		if (in_str('&', raw_token[j]))
			split_by_and(c_list, raw_sub_token, raw_token[j]);
	}

	free(raw_token);
	free(cmd_trim);
}
