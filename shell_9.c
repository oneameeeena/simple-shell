#include"shell.h"
/**
 * _isdigit - defines if str is number
 * @s: user_in str
 * Return: 1 if a number.otherwise 0.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}



/**
 * rev_str - reverses a str.
 * @s: user_in str.
 * Return: void.
 */
void rev_str(char *s)
{
	int count = 0, i, j;
	char *str, tmp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			tmp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = tmp;
		}
	}
}


/**
 * cd_shell - changes directory
 * @Data_sh: data
 * Return: 1 success
 */
int cd_shell(Data_sl *Data_sh)
{
	char *dir;
	int _home, _home2, i;

	dir = Data_sh->args[1];

	if (dir != NULL)
	{
		_home = _strcmp("$HOME", dir);
		_home2 = _strcmp("~", dir);
		i = _strcmp("--", dir);
	}

	if (dir == NULL || !_home || !_home2 || !i)
	{
		cd_home(Data_sh);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(Data_sh);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(Data_sh);
		return (1);
	}

	cd_to(Data_sh);

	return (1);
}


/**
 * cd_dot - changes directory
 * @Data_sh: data environ
 * Return: void
 */
void cd_dot(Data_sl *Data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	envSet("OLDPWD", cp_pwd, Data_sh);
	dir = Data_sh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		envSet("PWD", cp_pwd, Data_sh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_str(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		envSet("PWD", cp_strtok_pwd, Data_sh);
	}
	else
	{
		chdir("/");
		envSet("PWD", "/", Data_sh);
	}
	Data_sh->status = 0;
	free(cp_pwd);
}
