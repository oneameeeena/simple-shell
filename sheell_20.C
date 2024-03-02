#include"shell.h"
/**
 * cmd_spliter - splits cmd lines according to sep
 * @Data_sh: strcture
 * @user_in: user_in str
 * Return: 0 to exit
 */
int cmd_spliter(Data_sl *Data_sh, char *user_in)
{

	sperator_lst *head_s, *list_s;
	list_ln *head_l, *list_l;
	int lp;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, user_in);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		Data_sh->user_in = list_l->line;
		Data_sh->args = line_spliter(Data_sh->user_in);
		lp = exec_line(Data_sh);
		free(Data_sh->args);

		if (lp == 0)
			break;

		go_next(&list_s, &list_l, Data_sh);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sperator_lst(&head_s);
	free_list_ln(&head_l);

	if (lp == 0)
		return (0);
	return (1);
}

/**
 * line_spliter - tokenizes the user_in str
 *
 * @user_in: user_in str.
 * Return: str.
 */
char **line_spliter(char *user_in)
{
	size_t t_size;
	size_t i;
	char **tokens;
	char *token;

	t_size = TOK_BUFFERSIZE;
	tokens = malloc(sizeof(char *) * (t_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(user_in, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == t_size)
		{
			t_size += TOK_BUFFERSIZE;
			tokens = func_reallocdp(tokens, i, sizeof(char *) * t_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
