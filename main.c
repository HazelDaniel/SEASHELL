#include "utils/main.h"

/* GLOBAL DECLARATIONS */
comm_list_t *commands = NULL;
int comms_index = -1;
char **new_environ = NULL, *name, *callpwd;
trashenv_t *env_trash = NULL;
pathdir_t *path_list = NULL;
alias_t *aliases = NULL;
var_t *variables = NULL;
int hist;
char *prompts[10] =
{"_$ ", " ___(($USER@$hostname)-[$PWD]\n|___: ", "$"}, *prompt;

/**
 * handle_signal - the signal handler for CTRL-C
 * @sig: the signal in number
 * Return: nothing
 **/
void handle_signal(int sig)
{
	char *sig_str = _itoa(sig);

	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, handle_signal);
		fflush(stdin);
		write(STDIN_FILENO, "\n", 1);
		write(STDIN_FILENO, prompt, _strlen(prompt));
	}
}


/**
 * main - the entry point into the program
 * @argc: the argument count
 * @argv: the argument vector
 * @envp: the environment pointer
 * Return: int
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *buff = _getenv("x"), *test_str = "hello# world";
	char **cmd, *path_str;
	int status;
	size_t read = 0, size = 0, ret_count;

	_copyenv();
	set_exec_dir(argv);
	atexit(exec_on_exit);
	path_str = _getenv("PATH");
	linkpath(path_str);
	name = argv[0], (void)envp;
	hist = 1;

	while (1)
	{
		prompt = var_replace(prompts[1]);
		buff = malloc(BUFF_LEN * sizeof(char));
		printf("%s", prompt);
		signal(SIGINT, handle_signal);
		read = _getline(&buff, &size, STDIN_FILENO);
		if (read == EOF)
		{
			free(buff);
			break;
		}
		if (read != EOF)
		{
			status = parse_to_commands(buff);
			if (status == -1)
				return (status);
			ret_count += exec_all_commands();
			free_commands();
		}

		free(prompt), free(buff);
		buff = NULL, prompt = NULL;
	}

	cleanup();

	return (ret_count);
}
