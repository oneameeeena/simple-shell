#include"shell.h"
/**
 * func_realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr.
 * if malloc fails, NULL.
 */
void *func_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *dis_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	dis_ptr = malloc(new_size);
	if (dis_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(dis_ptr, ptr, new_size);
	else
		_memcpy(dis_ptr, ptr, old_size);

	free(ptr);
	return (dis_ptr);
}

/**
 * func_reallocdp - reallocates block of a double pointer.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, allocation .
 * @new_size: new size, in bytes - new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr.
 * if malloc fails, NULL.
 */
char **func_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **dis_ptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	dis_ptr = malloc(sizeof(char *) * new_size);
	if (dis_ptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		dis_ptr[i] = ptr[i];

	free(ptr);

	return (dis_ptr);
}


/**
 * get_len - check lent number.
 * @n: int.
 * Return: number lent.
 */
int get_len(int n)
{
	unsigned int n1;
	int lent = 1;

	if (n < 0)
	{
		lent++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lent++;
		n1 = n1 / 10;
	}

	return (lent);
}
/**
 * func_itoa - converts int to str.
 * @n: int
 * Return: String.
 */
char *func_itoa(int n)
{
	unsigned int n1;
	int lent = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lent + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lent) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lent--;
	do {
		*(buffer + lent) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lent--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts str to integer.
 * @s: user_in str.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
