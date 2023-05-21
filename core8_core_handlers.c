#include "utils/main.h"


int handle_cd(char **args)
{
	char *input;

	if (!args)
		input = NULL;
	else
		input = *args;

	if (cd(input, args) == 0)
		return (0);

	return (-1);
}

int handle_help(char **args)
{
	char *input;

	if (!args)
		input = NULL;
	else
		input = *args;

	if (help(input) == 0)
		return (0);
	
	return (-1);
}
