#include"shell.h"
/**
 * find_error - finds syntax errors
 *
 * @user_in: user_in str
 * @i: index
 * @last: last char read
 * Return: error index. 0
 * errors
 */
int find_error(char *user_in, int i, char last)
{
	int count;

	count = 0;
	if (*user_in == '\0')
		return (0);

	if (*user_in == ' ' || *user_in == '\t')
		return (find_error(user_in + 1, i + 1, last));

	if (*user_in == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*user_in == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = rep_char(user_in, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*user_in == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = rep_char(user_in, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (find_error(user_in + 1, i + 1, *user_in));
}

/**
 * first_char - finds index first char
 *
 * @user_in: user_in str
 * @i: index
 * Return: 1 if there is an error.
 */
int first_char(char *user_in, int *i)
{

	for (*i = 0; user_in[*i]; *i += 1)
	{
		if (user_in[*i] == ' ' || user_in[*i] == '\t')
			continue;

		if (user_in[*i] == ';' || user_in[*i] == '|' || user_in[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_error - prints error
 * @Data_sh: data strcture
 * @user_in: user_in str
 * @i: index of the error
 * @bool: control msg error
 * Return: void
 */
void print_error(Data_sl *Data_sh, char *user_in, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *count;
	int lent;

	if (user_in[i] == ';')
	{
		if (bool == 0)
			msg = (user_in[i + 1] == ';' ? ";;" : ";");
		else
			msg = (user_in[i - 1] == ';' ? ";;" : ";");
	}

	if (user_in[i] == '|')
		msg = (user_in[i + 1] == '|' ? "||" : "|");

	if (user_in[i] == '&')
		msg = (user_in[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	count = func_itoa(Data_sh->ln_count);
	lent = _strlen(Data_sh->av[0]) + _strlen(count);
	lent += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, Data_sh->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, lent);
	free(error);
	free(count);
}

/**
 * check_error - intermediate function to
 * find and print a syntax error
 *
 * @Data_sh: data strcture
 * @user_in: user_in str
 * Return: 1 if there is an error. 0 in other case
 */
int check_error(Data_sl *Data_sh, char *user_in)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(user_in, &begin);
	if (f_char == -1)
	{
		print_error(Data_sh, user_in, begin, 0);
		return (1);
	}

	i = find_error(user_in + begin, 0, *(user_in + begin));
	if (i != 0)
	{
		print_error(Data_sh, user_in, begin + i, 1);
		return (1);
	}

	return (0);
}
