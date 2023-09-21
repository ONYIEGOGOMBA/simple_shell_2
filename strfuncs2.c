#include "shell.h"

/**
 * _strchr - Locates a character in a string.
 * @m: The string to be searched.
 * @b: The character to be located.
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; m[index]; index++)
	{
		if (m[index] == b)
			return (m + index);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @m: The string to be searched.
 * @axep: The prefix to be measured.
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int byets = 0;
	int index;

	while (*m)
	{
		for (index = 0; axep[index]; index++)
		{
			if (*m == axep[index])
			{
				byets++;
				break;
			}
		}
		m++;
	}
	return (bytes);
}

/**
 * _strcmp - Compares two strings.
 * @m1: The first string to be compared.
 * @m2: The second string to be compared.
 * Return: Positive byte difference if m1 > m2
 *         0 if s1 = s2
 *         Negative byte difference if m1 < m2
 */
int _strcmp(char *m1, char *m2)
{
	while (*m1 && *m2 && *m1 == *m2)
	{
		m1++;
		m2++;
	}

	if (*m1 != *m2)
		return (*m1 - *m2);

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @m1: Pointer to a string.
 * @m2: Pointer to a string.
 * @f: The first n bytes of the strings to compare.
 * Return: Less than 0 if m1 is shorter than m2.
 *         0 if m1 and m2 match.
 *         Greater than 0 if m1 is longer than m2.
 */
int _strncmp(const char *m1, const char *m2, size_t f)
{
	size_t y;

	for (y = 0; m1[y] && m2[y] && y < f; y++)
	{
		if (m1[y] > m2[y])
			return (m1[y] - m2[y]);
		else if (m1[y] < m2[y])
			return (m1[y] - m2[y]);
	}
	if (y == f)
		return (0);
	else
		return (-15);
}
