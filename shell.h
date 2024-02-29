#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFERSIZE 1024
#define TOK_BUFFERSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - data struct
 * @av: 1st args char
 * @user_in: 2nd args int
 * @args: 3rd args char
 * @status: arg
 * @ln_count: arg
 * @var_environ: arg
 * @pid: arg
 *
 * Description: structure data
 */
typedef struct data
{
	char **av;
	char *user_in;
	char **args;
	int status;
	int ln_count;
	char **var_environ;
	char *pid;
} Data_sl;

/**
 * struct sperator_lst_s - sperator_lst_s struct
 * @separator: 1st args char
 * @next: 2nd args char
 * Description: structure
 */
typedef struct sperator_lst_s
{
	char separator;
	struct sperator_lst_s *next;
} sperator_lst;

/**
 * struct LineList - LineList struct
 * @line: 1st args char
 * @next: 2nd args char
 * Description: structure
 */
typedef struct LineList
{
	char *line;
	struct LineList *next;
} list_ln;

/**
 * struct StoreVar_list - StoreVar_list struct
 * @len_var: arg
 * @val: arg
 * @len_val:arg
 * @next:arg
 * Description: structure
 */
typedef struct StoreVar_list
{
	int len_var;
	char *val;
	int len_val;
	struct StoreVar_list *next;
} StoreVar;

/**
 * struct builtin_s - builtin_s struct
 * @cmd_name: arg
 * @f: arg
 * Description: structure
 */
typedef struct builtin_s
{
	char *cmd_name;
	int (*f)(Data_sl *Data_sh);
} builtin_s;

sperator_lst *add_node(sperator_lst **head, char sep);
void free_sperator_lst(sperator_lst **head);
list_ln *AddLineNode(list_ln **head, char *line);
void free_list_ln(list_ln **head);
StoreVar *add_Storevar(StoreVar **head, int lenvar, char *var, int lenval);

void free_StoreVar(StoreVar **head);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

int _strspn(char *s, char *autorise);
void _memcpy(void *dis_ptr, const void *ptr, unsigned int size);
void *func_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **func_reallocdp
(char **ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(const char *s);

int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_str(char *s);

int rep_char(char *user_in, int i);
int find_error(char *user_in, int i, char last);
int first_char(char *user_in, int *i);
void print_error(Data_sl *Data_sh, char *user_in, int i, int bool);
int check_error(Data_sl *Data_sh, char *user_in);

char *cls_comment(char *in);
void shell_loop(Data_sl *Data_sh);
char *read_line(int *End_of);
char *swap_char(char *user_in, int bool);
void add_nodes(sperator_lst **head_s, list_ln **head_l, char *user_in);

void go_next(sperator_lst **list_s, list_ln **list_l, Data_sl *Data_sh);
int cmd_spliter(Data_sl *Data_sh, char *user_in);
char **line_spliter(char *user_in);
void check_env(StoreVar **h, char *in, Data_sl *data);
int check_vars(StoreVar **h, char *in, char *st, Data_sl *data);

char *replaced_user_in
(StoreVar **head, char *user_in, char *new_user_in, int nlen);
char *rep_var(char *user_in, Data_sl *Data_sh);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int exec_line(Data_sl *Data_sh);

int is_cdir(char *path, int *i);
char *_which(char *cmd, char **var_environ);
int exe_cmd(Data_sl *Data_sh);
int check_error_cmd(char *dir, Data_sl *Data_sh);
int cmd_exec(Data_sl *Data_sh);

char *get_env(const char *cmd_name, char **var_environ);
int _env(Data_sl *Data_sh);
char *copy_info(char *cmd_name, char *value);
void envSet(char *cmd_name, char *value, Data_sl *Data_sh);
int env_Set(Data_sl *Data_sh);

int _unset_env(Data_sl *Data_sh);
void cd_dot(Data_sl *Data_sh);
void cd_to(Data_sl *Data_sh);
void cd_prev(Data_sl *Data_sh);
void cd_home(Data_sl *Data_sh);

int cd_shell(Data_sl *Data_sh);
int (*get_builtin(char *cmd))(Data_sl *Data_sh);
int exit_shell(Data_sl *Data_sh);
int get_len(int n);
char *func_itoa(int n);

int _atoi(char *s);
char *strcat_cd(Data_sl *, char *, char *, char *);
char *error_get_cd(Data_sl *Data_sh);
char *error_not_found(Data_sl *Data_sh);
char *error_exit_shell(Data_sl *Data_sh);

char *error_get_alias(char **args);
char *error_env(Data_sl *Data_sh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path(Data_sl *Data_sh);

int get_error(Data_sl *Data_sh, int eval);
void get_sigint(int sig);
void c_env(void);
void func_helper_set_env(void);
void func_helper_unset_env(void);

void func_helper_general(void);
void func_helper_exit(void);
void func_helper(void);
void func_helper_alias(void);
void func_helper_cd(void);

int msg_help(Data_sl *Data_sh);
void hundel_ctrd(int s);
void set_data(Data_sl *Data_sh, char **av);
void free_data(Data_sl *Data_sh);
void func_helper_env(void);

#endif
