#include"shell.h"
/**
 * strcat_cd - function concatenates error
 *
 * @Data_sh: data (directory)
 * @msg: message
 * @error: stdout msg
 * @ver_str: ln_count lines
 * Return: error
 */
char *strcat_cd(Data_sl *Data_sh, char *msg, char *error, char *ver_str)
{
	char *NoPermited_flag;

	_strcpy(error, Data_sh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, Data_sh->args[0]);
	_strcat(error, msg);
	if (Data_sh->args[1][0] == '-')
	{
		NoPermited_flag = malloc(3);
		NoPermited_flag[0] = '-';
		NoPermited_flag[1] = Data_sh->args[1][1];
		NoPermited_flag[2] = '\0';
		_strcat(error, NoPermited_flag);
		free(NoPermited_flag);
	}
	else
	{
		_strcat(error, Data_sh->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message to cmd get_cd
 * @Data_sh: data directory
 * Return: Error
 */
char *error_get_cd(Data_sl *Data_sh)
{
	int lent, idLent;
	char *error, *ver_str, *msg;

	ver_str = func_itoa(Data_sh->ln_count);
	if (Data_sh->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		idLent = 2;
	}
	else
	{
		msg = ": can't cd to ";
		idLent = _strlen(Data_sh->args[1]);
	}

	lent = _strlen(Data_sh->av[0]) + _strlen(Data_sh->args[0]);
	lent += _strlen(ver_str) + _strlen(msg) + idLent + 5;
	error = malloc(sizeof(char) * (lent + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(Data_sh, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error command not found
 * @Data_sh: data (ln_count, arguments)
 * Return: Error
 */
char *error_not_found(Data_sl *Data_sh)
{
	int lent;
	char *error;
	char *ver_str;

	ver_str = func_itoa(Data_sh->ln_count);
	lent = _strlen(Data_sh->av[0]) + _strlen(ver_str);
	lent += _strlen(Data_sh->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - generic error exit
 * @Data_sh: data (ln_count, arguments)
 *
 * Return: Error
 */
char *error_exit_shell(Data_sl *Data_sh)
{
	int lent;
	char *error;
	char *ver_str;

	ver_str = func_itoa(Data_sh->ln_count);
	lent = _strlen(Data_sh->av[0]) + _strlen(ver_str);
	lent += _strlen(Data_sh->args[0]) + _strlen(Data_sh->args[1]) + 23;
	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, Data_sh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, Data_sh->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, Data_sh->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
