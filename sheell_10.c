#include"shell.h"
/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @Data_sh: data relevant (directories)
 * Return: void
 */
void cd_to(Data_sl *Data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = Data_sh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(Data_sh, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	envSet("OLDPWD", cp_pwd, Data_sh);

	cp_dir = _strdup(dir);
	envSet("PWD", cp_dir, Data_sh);

	free(cp_pwd);
	free(cp_dir);

	Data_sh->status = 0;

	chdir(dir);
}

/**
 * cd_prev - changes to the previous directory
 *
 * @Data_sh: data relevant (environ)
 * Return: void
 */
void cd_prev(Data_sl *Data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = get_env("OLDPWD", Data_sh->var_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	envSet("OLDPWD", cp_pwd, Data_sh);

	if (chdir(cp_oldpwd) == -1)
		envSet("PWD", cp_pwd, Data_sh);
	else
		envSet("PWD", cp_oldpwd, Data_sh);

	p_pwd = get_env("PWD", Data_sh->var_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	Data_sh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes directory
 * @Data_sh: environ
 * Return: void
 */
void cd_home(Data_sl *Data_sh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = get_env("HOME", Data_sh->var_environ);

	if (home == NULL)
	{
		envSet("OLDPWD", p_pwd, Data_sh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(Data_sh, 2);
		free(p_pwd);
		return;
	}

	envSet("OLDPWD", p_pwd, Data_sh);
	envSet("PWD", home, Data_sh);
	free(p_pwd);
	Data_sh->status = 0;
}


/**
 * rep_char - counts the repetitions
 *
 * @user_in: user_in str
 * @i: index
 * Return: repetitions
 */
int rep_char(char *user_in, int i)
{
	if (*(user_in - 1) == *user_in)
		return (rep_char(user_in - 1, i + 1));

	return (i);
}
