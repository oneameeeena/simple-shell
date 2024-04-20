#include"shell.h"
/**
 * _strspn - gets the length of a prefix substr.
 * @s: initial segment.
 * @autorise: autoriseed bytes.
 * Return: count accepted bytes.
 */
int _strspn(char *s, char *autorise)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(autorise + j) != '\0'; j++)
		{
			if (*(s + i) == *(autorise + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}


/**
 * _strdup - duplicates a str in the heap.
 * @s: char pointer str
 * Return: duplicated
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - lenght of a str.
 * @s: char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars of strs
 * @str: user_in str.
 * @delim: delimiter.
 *
 * Return: 1 if true , 0 false.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a str delimiter.
 * @str: user_in str.
 * @delim: delimiter.
 *
 * Return: str.
 */
char *_strtok(char str[], const char *delim)
{
	static char *spltd, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		spltd = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = spltd;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *spltd; spltd++)
	{
		if (spltd != str_start)
			if (*spltd && *(spltd - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*spltd == delim[i])
			{
				*spltd = '\0';
				if (spltd == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *spltd) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}
