#include"shell.h"
/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @var_environ: environment var
 * Return: location of the command.
 */
char *_which(char *cmd, char **var_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = get_env("PATH", var_environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * exe_cmd - determines if is an executable
 *
 * @Data_sh: data strcture
 * Return: 0 if is not an executable, other number if it does
 */
int exe_cmd(Data_sl *Data_sh)
{
	struct stat st;
	int i;
	char *user_in;

	user_in = Data_sh->args[0];
	for (i = 0; user_in[i]; i++)
	{
		if (user_in[i] == '.')
		{
			if (user_in[i + 1] == '.')
				return (0);
			if (user_in[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (user_in[i] == '/' && i != 0)
		{
			if (user_in[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(user_in + i, &st) == 0)
	{
		return (i);
	}
	get_error(Data_sh, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @Data_sh: data strcture
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, Data_sl *Data_sh)
{
	if (dir == NULL)
	{
		get_error(Data_sh, 127);
		return (1);
	}

	if (_strcmp(Data_sh->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(Data_sh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(Data_sh->args[0], X_OK) == -1)
		{
			get_error(Data_sh, 126);
			return (1);
		}
	}

	return (0);
}
