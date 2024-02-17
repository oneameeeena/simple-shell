#include "SHELL.H"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check 
 *
 * Return: length integer length of string 
 */
int _strlen(char *s)
{
	int i = 0; 
	if (!s)
		return (0); 

	while (*s++)
		i++;
	return (i);
}

