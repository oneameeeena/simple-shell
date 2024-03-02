#include"shell.h"
/**
 * free_data - frees data strcture
 *
 * @Data_sh: data strcture
 * Return: void
 */
void free_data(Data_sl *Data_sh)
{
	unsigned int i;

	for (i = 0; Data_sh->var_environ[i]; i++)
	{
		free(Data_sh->var_environ[i]);
	}

	free(Data_sh->var_environ);
	free(Data_sh->pid);
}

/**
 * set_data - Initialize data strcture
 *
 * @Data_sh: data strcture
 * @av: argument vector
 * Return: void
 */
void set_data(Data_sl *Data_sh, char **av)
{
	unsigned int i;

	Data_sh->av = av;
	Data_sh->user_in = NULL;
	Data_sh->args = NULL;
	Data_sh->status = 0;
	Data_sh->ln_count = 1;

	for (i = 0; environ[i]; i++)
		;

	Data_sh->var_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		Data_sh->var_environ[i] = _strdup(environ[i]);
	}

	Data_sh->var_environ[i] = NULL;
	Data_sh->pid = func_itoa(getpid());
}

/**
 * read_line - reads the user_in str.
 * @End_of: return value of getline function
 * Return: user_in str
 */
char *read_line(int *End_of)
{
	char *user_in = NULL;
	size_t buffersize = 0;

	*End_of = getline(&user_in, &buffersize, stdin);

	return (user_in);
}


/**
 * check_env - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: user_in str
 * @data: data strcture
 * Return: void
 */
void check_env(StoreVar **h, char *in, Data_sl *data)
{
	int row, chr, j, lenval;
	char **_envr;

	_envr = data->var_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lenval = _strlen(_envr[row] + chr + 1);
				add_Storevar(h, j, _envr[row] + chr + 1, lenval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_Storevar(h, j, NULL, 0);
}
