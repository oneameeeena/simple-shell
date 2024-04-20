#include"shell.h"
/**
 * cmd_exec - executes cmd lines
 *
 * @Data_sh: data relevant (args and user_in)
 * Return: 1 on success.
 */
int cmd_exec(Data_sl *Data_sh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = exe_cmd(Data_sh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(Data_sh->args[0], Data_sh->var_environ);
		if (check_error_cmd(dir, Data_sh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(Data_sh->args[0], Data_sh->var_environ);
		else
			dir = Data_sh->args[0];
		execve(dir + exec, Data_sh->args, Data_sh->var_environ);
	}
	else if (pd < 0)
	{
		perror(Data_sh->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	Data_sh->status = state / 256;
	return (1);
}


/**
 * cmp_env_cmd_name - compares env variables names
 * with the cmd_name passed.
 * @nenv: name of the environment var
 * @cmd_name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_cmd_name(const char *nenv, const char *cmd_name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != cmd_name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * get_env - get an environment var
 * @cmd_name: name of the environment var
 * @var_environ: environment var
 *
 * Return: value of the environment var if is found.
 * In other case, returns NULL.
 */
char *get_env(const char *cmd_name, char **var_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment vars */
	/* environ is declared in the header file */
	for (i = 0; var_environ[i]; i++)
	{
		mov = cmp_env_cmd_name(var_environ[i], cmd_name);
		if (mov)
		{
			ptr_env = var_environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @Data_sh: data relevant.
 * Return: 1 on success.
 */
int _env(Data_sl *Data_sh)
{
	int i, j;

	for (i = 0; Data_sh->var_environ[i]; i++)
	{

		for (j = 0; Data_sh->var_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, Data_sh->var_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	Data_sh->status = 0;

	return (1);
}
