#include"shell.h"
/**
 * copy_info - copies info to create
 * a new env or alias
 * @cmd_name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *copy_info(char *cmd_name, char *value)
{
	char *new;
	int len_cmd_name, len_value, len;

	len_cmd_name = _strlen(cmd_name);
	len_value = _strlen(value);
	len = len_cmd_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, cmd_name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * envSet - sets an environment var
 * @cmd_name: name of the environment var
 * @value: value of the environment var
 * @Data_sh: data strcture (environ)
 * Return: void
 */
void envSet(char *cmd_name, char *value, Data_sl *Data_sh)
{
	int i;
	char *var_env, *cmd_name_env;

	for (i = 0; Data_sh->var_environ[i]; i++)
	{
		var_env = _strdup(Data_sh->var_environ[i]);
		cmd_name_env = _strtok(var_env, "=");
		if (_strcmp(cmd_name_env, cmd_name) == 0)
		{
			free(Data_sh->var_environ[i]);
			Data_sh->var_environ[i] = copy_info(cmd_name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	Data_sh->var_environ =
	func_reallocdp(Data_sh->var_environ, i, sizeof(char *) * (i + 2));
	Data_sh->var_environ[i] = copy_info(cmd_name, value);
	Data_sh->var_environ[i + 1] = NULL;
}

/**
 * env_Set - compares env var names
 * with the name passed.
 * @Data_sh: data relevant (env cmd_name and env value)
 * Return: 1 on success.
 */
int env_Set(Data_sl *Data_sh)
{

	if (Data_sh->args[1] == NULL || Data_sh->args[2] == NULL)
	{
		get_error(Data_sh, -1);
		return (1);
	}

	envSet(Data_sh->args[1], Data_sh->args[2], Data_sh);

	return (1);
}

/**
 * _unset_env - deletes a environment var
 * @Data_sh: data relevant (env cmd_name)
 * Return: 1 on success.
 */
int _unset_env(Data_sl *Data_sh)
{
	char **reallocvar_environ;
	char *var_env, *cmd_name_env;
	int i, j, k;

	if (Data_sh->args[1] == NULL)
	{
		get_error(Data_sh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; Data_sh->var_environ[i]; i++)
	{
		var_env = _strdup(Data_sh->var_environ[i]);
		cmd_name_env = _strtok(var_env, "=");
		if (_strcmp(cmd_name_env, Data_sh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(Data_sh, -1);
		return (1);
	}
	reallocvar_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; Data_sh->var_environ[i]; i++)
	{
		if (i != k)
		{
			reallocvar_environ[j] = Data_sh->var_environ[i];
			j++;
		}
	}
	reallocvar_environ[j] = NULL;
	free(Data_sh->var_environ[k]);
	free(Data_sh->var_environ);
	Data_sh->var_environ = reallocvar_environ;
	return (1);
}
