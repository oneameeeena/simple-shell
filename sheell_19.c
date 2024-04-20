#include"shell.h"
/**
 * shell_loop - looper
 * @Data_sh: data (av, user_in, args)
 * Return: void.
 */
void shell_loop(Data_sl *Data_sh)
{
	int prompte, End_of;
	char *user_in;

	prompte = 1;
	while (prompte == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		user_in = read_line(&End_of);
		if (End_of != -1)
		{
			user_in = cls_comment(user_in);
			if (user_in == NULL)
				continue;

			if (check_error(Data_sh, user_in) == 1)
			{
				Data_sh->status = 2;
				free(user_in);
				continue;
			}
			user_in = rep_var(user_in, Data_sh);
			prompte = cmd_spliter(Data_sh, user_in);
			Data_sh->ln_count += 1;
			free(user_in);
		}
		else
		{
			prompte = 0;
			free(user_in);
		}
	}
}


/**
 * swap_char - swaps | and & for non-printed char
 * @user_in: user_in str
 * @bool: swap
 * Return: swapped str
 */
char *swap_char(char *user_in, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; user_in[i]; i++)
		{
			if (user_in[i] == '|')
			{
				if (user_in[i + 1] != '|')
					user_in[i] = 16;
				else
					i++;
			}

			if (user_in[i] == '&')
			{
				if (user_in[i + 1] != '&')
					user_in[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; user_in[i]; i++)
		{
			user_in[i] = (user_in[i] == 16 ? '|' : user_in[i]);
			user_in[i] = (user_in[i] == 12 ? '&' : user_in[i]);
		}
	}
	return (user_in);
}

/**
 * add_nodes - add separators and cmd lines in the lists
 * @head_s: head separator list
 * @head_l: head cmd lines list
 * @user_in: user_in str
 * Return: void
 */
void add_nodes(sperator_lst **head_s, list_ln **head_l, char *user_in)
{
	int i;
	char *ln;

	user_in = swap_char(user_in, 0);

	for (i = 0; user_in[i]; i++)
	{
		if (user_in[i] == ';')
			add_node(head_s, user_in[i]);

		if (user_in[i] == '|' || user_in[i] == '&')
		{
			add_node(head_s, user_in[i]);
			i++;
		}
	}

	ln = _strtok(user_in, ";|&");
	do {
		ln = swap_char(ln, 1);
		AddLineNode(head_l, ln);
		ln = _strtok(NULL, ";|&");
	} while (ln != NULL);

}

/**
 * go_next - go to the next cmd
 * @list_s: separator list
 * @list_l: cmd line list
 * @Data_sh: strcture
 * Return: void
 */
void go_next(sperator_lst **list_s, list_ln **list_l, Data_sl *Data_sh)
{
	int check_sep;
	sperator_lst *ls_s;
	list_ln *ls_l;

	check_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && check_sep)
	{
		if (Data_sh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				check_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				check_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !check_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
