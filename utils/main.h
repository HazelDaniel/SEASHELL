#ifndef ___MAIN_
#define ___MAIN_
#include <stddef.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/* MACROS */
#define __cp__(x, y) (_strcpy(&x, &y))
#define _al_len_(x) ((_len_p((void **)x)) + (1))
#define EXIT (-3)
#define BUFF_LEN 1024

/* STRUCTURES AND DECLARATIONS */
typedef struct command
{
	char *separator;
	char *command;
	int *status;
	int id;
	int is_linked;
	struct command *list;
	struct command *next;
} comm_t;

typedef comm_t *comm_list_t;

typedef struct trash_env
{
	char *value;
	int *index;
	struct trash_env *next;
} trashenv_t;

typedef struct var_env
{
	char *value;
	struct var_env *next;
}	var_t;

typedef struct path_dir
{
	char *dir;
	struct path_dir *next;
} pathdir_t;

typedef struct alias
{
	char *value;
	struct alias *next;
} alias_t;

typedef struct wtok
{
	int check_points[1024];
	char vals[1024];
} wtok_t;

typedef struct builtin_s
{
	char *name;
	int (* f)(char **list);
} builtin_t;

extern char **environ;
extern char **new_environ;
extern comm_list_t *commands;
extern int comms_index;
extern trashenv_t *env_trash;
extern pathdir_t *path_list;
extern alias_t *aliases;
extern var_t *variables;
extern char *name;
extern int hist;
extern int errno;
extern char *callpwd;


/* STRING UTILS */
char *_strtok(char *str, char *delim);
char **_splitstr(char *str, char *delim);
char *_trim(char *str);
int in_str(char c, char *str);
int is_print(char c);
char *_strcpy(char (*dest)[1024], char **src);
int _len_p(void **p);
char *_strddup(char *src);
int _strcmp(char *str1, char *str2);
unsigned int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strdcat(char *dest, char *src);
int adj_char_num(char *str, char c, int i);
int first_oc_of(char *str, char c);
int first_oc(int (* f)(char c), char *str);
int is_start_str(char *strsub, char *strsup);
int is_end_str(char *strsub, char *strsup);
char * rm_tr_slash(char *str);
char *join_list(char **list);
char **word_tok(char *str);
wtok_t *gen_tok(char *str);


/* MEMORY UTILS */
void free_str_arr(char **str_arr, int is_dyn);
void **_realloc_ptr(void *ptr, size_t old_size, size_t size);
void *_realloc(void *ptr, size_t old_size, size_t size);
void _memcpy(void *ptr, const void *newptr, unsigned int size);
void _memcpy_ptr(void **ptr, void **newptr, unsigned int size);

/* LIST UTILS */
void append_comm_list(comm_list_t list);
void append_comm(comm_list_t* list, char separator,
	const char* command, int status);
comm_t *prepend_comm(comm_list_t* list, char separator,
	const char* command, int status);
void print_comms(const comm_list_t list);
void clear_comms(comm_list_t list);
void print_comms_full();
void remove_command(comm_t *list, int value);
trashenv_t *get_trash(trashenv_t *list, char *value);
void append_trash(char *value, int index);
void remove_trash(trashenv_t *list, char *value);
void clear_trash(trashenv_t *list);
void print_trash(trashenv_t *list);
trashenv_t *pop_trash();
pathdir_t *linkpath(char *path);
void append_path(char *value);
void print_path();
void free_path();

/* SPLIT UTILS */
void split_by_or(comm_list_t *c_list,
	char **all_c, char *curr_token);
void split_by_and(comm_list_t *c_list,
	char **raw_token, char *curr_token);
void split_by_and_or_order(comm_list_t *c_list,
	char **raw_token, char *curr_token);
void split_by_or_and_order(comm_list_t *c_list,
	char **raw_token, char *curr_token);

/* STATE UTILS */
void empty_state_buff(char *delim);
void cleanup();

/* COMMAND HANDLERS */
int parse_to_commands(char *string);
void handle_parsed_commands(char **);
void free_commands();
int exec_all_commands();
int exec_comms(const comm_list_t list);

/*_________________CORE___________________*/
/* ENVIRONMENT HANDLERS */
int getall_env();
char *_getenv(char *input);
int _setenv(char *input1, char *input2);
int _unsetenv(char *value);
void _copyenv();
void _freenv();

/* PATH HANDLERS */
char *_trace(char *input);

/* INPUT HANDLERS */
ssize_t _getline(char **line_addr, size_t *n, FILE *stream);

/* ALIAS HANDLERS */
char *_getalias(char *input);
char *_setalias(char *input);
int alias(char *input);
void free_aliases(alias_t *list);
void print_aliases();

/* SHELL VARIABLES */
void _getall_vars();
char *_getvar(char *input);
char *_setvar(char *input);
void free_vars(var_t *list);
char *lookup_var(char *input);
char *expand(char *input);
char* var_replace(const char* string);

/* MISC */
int find_max(int num1, int num2);
int is_word(char c);
int is_hwp(char c);
int is_print(char c);
int last_oc_of(char *str, char c);
int last_oc(int (* f)(char c), char *str);
int last_spn_oc(int (* f)(char c), char *str);
char *_itoa(int num);
int dig_len(int num);
char *comment_line(char **buff_ptr);
void norm_dyn_str(char **str_ptr);
char * _strchr(const char *str, char c);
char* _strncpy(char* dest, const char* src, size_t n);
void trim_str_arr(char **args);
void format_args(char **args);
int is_graph(char c);
int is_dot(char c);
int is_tilde(char c);
int is_hyp(char c);

/* BUILTINS  AND HANDLERS */
int (*get_builtin(char *command))(char **list);
int exit_(char *status, char **list);
int cd(char *loc, char **list);
int help(char *command);

int handle_alias(char **args);
int handle_unset_env(char **args);
int handle_set_env(char **args);
int handle_print_env(char **args);
int handle_cd(char **args);
int handle_help(char **args);
int handle_exit(char **args);
int handle_nothing(char **args);

/* CORE UTILS */
int execute(char *command);
int create_ex_stat(int status);
int create_pid(int pid);
void exec_on_exit(void);
void set_exec_dir(char *argv[]);

/* ERROR HANDLERS */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* HELP HANDLERS */
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

#define MVL 128

#endif/*___MAIN_*/
