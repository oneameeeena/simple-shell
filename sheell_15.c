#include"shell.h"
/**
 * exec_line - finds builtins and commands
 * @Data_sh: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(Data_sl *Data_sh)
{
	int (*builtin)(Data_sl *Data_sh);

	if (Data_sh->args[0] == NULL)
		return (1);

	builtin = get_builtin(Data_sh->args[0]);

	if (builtin != NULL)
		return (builtin(Data_sh));

	return (cmd_exec(Data_sh));
}


/**
 * exit_shell - exits the shell
 * @Data_sh: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(Data_sl *Data_sh)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (Data_sh->args[1] != NULL)
	{
		ustatus = _atoi(Data_sh->args[1]);
		is_digit = _isdigit(Data_sh->args[1]);
		str_len = _strlen(Data_sh->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(Data_sh, 2);
			Data_sh->status = 2;
			return (1);
		}
		Data_sh->status = (ustatus % 256);
	}
	return (0);
}


/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(Data_sl *)
{
	builtin_s builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", env_Set },
		{ "unset_env", _unset_env },
		{ "cd", cd_shell },
		{ "help", msg_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].cmd_name; i++)
	{
		if (_strcmp(builtin[i].cmd_name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}


/**
 * get_error - calls the error according the builtin, syntax or permission
 * @Data_sh: data strcture that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(Data_sl *Data_sh, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(Data_sh);
		break;
	case 126:
		error = error_path(Data_sh);
		break;
	case 127:
		error = error_not_found(Data_sh);
		break;
	case 2:
		if (_strcmp("exit", Data_sh->args[0]) == 0)
			error = error_exit_shell(Data_sh);
		else if (_strcmp("cd", Data_sh->args[0]) == 0)
			error = error_get_cd(Data_sh);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	Data_sh->status = eval;
	return (eval);
}
