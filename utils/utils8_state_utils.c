#include "main.h"

void empty_state_buff(char *delim)
{
	while(_strtok(NULL, delim))
		;
}
