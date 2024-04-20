#include"shell.h"
/**
 * func_helper_cd - for the builtin alias.
 * Return: void
 */
void func_helper_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * add_node - adds a separator at the end
 * of a sperator_lst.
 * @head: head
 * @sep: separator (; | &).
 * Return: address of the head.
 */
sperator_lst *add_node(sperator_lst **head, char sep)
{
	sperator_lst *new, *tmp;

	new = malloc(sizeof(sperator_lst));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_sperator_lst - frees a sperator_lst
 * @head: head of the linked list.
 * Return: void.
 */
void free_sperator_lst(sperator_lst **head)
{
	sperator_lst *tmp;
	sperator_lst *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tmp = curr) != NULL)
		{
			curr = curr->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * AddLineNode - adds a cmd line at the end
 * of list_ln.
 * @head: head.
 * @line: cmd line.
 * Return: head adresse
 */
list_ln *AddLineNode(list_ln **head, char *line)
{
	list_ln *new, *tmp;

	new = malloc(sizeof(list_ln));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}
