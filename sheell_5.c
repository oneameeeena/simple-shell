#include"shell.h"
/**
 * free_list_ln - frees list_ln
 * @head: head link list.
 * Return: void.
 */
void free_list_ln(list_ln **head)
{
	list_ln *tmp;
	list_ln *curr;

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
 * add_Storevar - adds a variable at the end
 * StoreVar list.
 * @head: head
 * @lenvar: var length
 * @val: value of the variable.
 * @lenval: length of the value.
 * Return: address of the head.
 */
StoreVar *add_Storevar(StoreVar **head, int lenvar, char *val, int lenval)
{
	StoreVar *new, *tmp;

	new = malloc(sizeof(StoreVar));
	if (new == NULL)
		return (NULL);

	new->len_var = lenvar;
	new->val = val;
	new->len_val = lenval;

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
 * free_StoreVar - frees StoreVar list
 * @head: head.
 * Return: void.
 */
void free_StoreVar(StoreVar **head)
{
	StoreVar *tmp;
	StoreVar *curr;

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
 * _memcpy - copies between void pointers.
 * @dis_ptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: void.
 */
void _memcpy(void *dis_ptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_dis_ptr = (char *)dis_ptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_dis_ptr[i] = char_ptr[i];
}
