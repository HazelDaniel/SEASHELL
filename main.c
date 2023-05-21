#include "utils/main.h"

/* GLOBAL DECLARATIONS */
comm_list_t *commands = NULL;
int comms_index;
char **new_environ = NULL, *name;
trashenv_t *env_trash = NULL;
pathdir_t *path_list = NULL;
alias_t *aliases = NULL;
var_t *variables = NULL;
int hist;

/**
 * main - the entry point into the program
 * Return: int
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *buff = _getenv("x");

	_copyenv();
	name = argv[0], (void)envp;
	hist = 1;
	
	printf("buff is %s\n", buff);
	alias("a=x");

	_freenv();
	free_aliases(aliases);
	free_vars(variables);

	return (0);
}
