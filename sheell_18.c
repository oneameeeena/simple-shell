#include"shell.h"
/**
 * check_vars - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: user_in str
 * @st: last status of the Shell
 * @data: data strcture
 * Return: void
 */
int check_vars(StoreVar **h, char *in, char *st, Data_sl *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_Storevar(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_Storevar(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_Storevar(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_Storevar(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_Storevar(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_Storevar(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_Storevar(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_user_in - replaces str into variables
 * @head: head of the linked list
 * @user_in: user_in str
 * @new_user_in: new user_in str (replaced)
 * @nlen: new length
 * Return: replaced str
 */
char *replaced_user_in(StoreVar **head, char *user_in,
char *new_user_in, int nlen)
{
	StoreVar *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (user_in[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_user_in[i] = user_in[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_user_in[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_user_in[i] = user_in[j];
			j++;
		}
	}

	return (new_user_in);
}

/**
 * rep_var - calls functions to replace str into vars
 * @user_in: user_in str
 * @Data_sh: data strcture
 * Return: replaced str
 */
char *rep_var(char *user_in, Data_sl *Data_sh)
{
	StoreVar *head, *indx;
	char *status, *new_user_in;
	int olen, nlen;

	status = func_itoa(Data_sh->status);
	head = NULL;

	olen = check_vars(&head, user_in, status, Data_sh);

	if (head == NULL)
	{
		free(status);
		return (user_in);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_user_in = malloc(sizeof(char) * (nlen + 1));
	new_user_in[nlen] = '\0';

	new_user_in = replaced_user_in(&head, user_in, new_user_in, nlen);

	free(user_in);
	free(status);
	free_StoreVar(&head);

	return (new_user_in);
}


/**
 * cls_comment - clear comments from user_in
 * @in: user_in str
 * Return: user_in
 */
char *cls_comment(char *in)
{
	int i, j;

	j = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				j = i;
		}
	}

	if (j != 0)
	{
		in = func_realloc(in, i, j + 1);
		in[j] = '\0';
	}

	return (in);
}
