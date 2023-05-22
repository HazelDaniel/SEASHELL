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
char *prompts[10] = {"_$ ", " ___(($USER@$hostname)-[$PWD]\n|___: ", "$"}, *prompt;

void handle_signal(int sig)
{
	char *flush_prompt = "\n";

	(void)sig, prompt = var_replace(prompts[1]);
	signal(SIGINT, handle_signal);
	fflush(stdin);
	write(STDIN_FILENO, flush_prompt, 1);
	write(STDIN_FILENO, prompt, _strlen(prompt));
}

/**
 * main - the entry point into the program
 * Return: int
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *buff = _getenv("x"), *test_str = "hello# world";
	char *command_list = "\tls || echo hello world ; alx-milestones && echo hello world ; ps && pwd || head -n 1 && la";
	char **cmd;
	int status;
	size_t read, size = 0;

	_copyenv();
	name = argv[0], (void)envp;
	hist = 1;
	
	// buff = comment_line(&test_str);
	prompt = var_replace(prompts[1]);
	while (1)
	{
		buff = malloc(1024 * sizeof(char *));
		if (read == EOF)
			break;
		else
			printf("%s", prompt);
		signal(SIGINT, handle_signal);
		read = _getline(&buff, &size, STDIN_FILENO);
		if (read != -1)
		{
			status = parse_to_commands(buff);
			if (status == -1)
				return (status);
			print_comms_full();
		}
		free(buff);
		buff = NULL;
	}

	free(prompt);
	_freenv();
	free_aliases(aliases);
	free_vars(variables);

	return (0);
}
