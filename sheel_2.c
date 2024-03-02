#include"shell.h"
/**
 * error_env - error message to get_env.
 * @Data_sh: data (ln_count, arguments)
 * Return: error.
 */
char *error_env(Data_sl *Data_sh)
{
	int lent;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = func_itoa(Data_sh->ln_count);
	msg = ": Unable to add/remove from environment\n";
	lent = _strlen(Data_sh->av[0]) + _strlen(ver_str);
	lent += _strlen(Data_sh->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, Data_sh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, Data_sh->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path - error path permission denied
 * @Data_sh: data (ln_count, arguments).
 * Return: error.
 */
char *error_path(Data_sl *Data_sh)
{
	int lent;
	char *ver_str;
	char *error;

	ver_str = func_itoa(Data_sh->ln_count);
	lent = _strlen(Data_sh->av[0]) + _strlen(ver_str);
	lent += _strlen(Data_sh->args[0]) + 24;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, Data_sh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, Data_sh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * func_helper_env - Helper for the builtin env
 * Return: void
 */
void func_helper_env(void)
{
	char *help = "env: env [option] [cmd_name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

}
/**
 * func_helper_set_env - Help for builtin setenv
 * Return: void
 */
void func_helper_set_env(void)
{

	char *help = "setenv: setenv (const char *cmd_name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * func_helper_unset_env - Help for unset_env
 * Return: void
 */
void func_helper_unset_env(void)
{
	char *help = "unset_env: unset_env (const char *cmd_name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
