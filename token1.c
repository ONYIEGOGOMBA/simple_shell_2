#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @f: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *f)
{
	int y, k, q, w, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!f)
		f = " ";
	for (y = 0; str[y] != '\0'; y++)
		if (!is_dell(str[y], f) && (is_dell(str[y + 1], f) || !str[y + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, k = 0; k < numwords; k++)
	{
		while (is_dell(str[y], f))
			y++;
		q = 0;
		while (!is_dell(str[y + q], f) && str[y + q])
			q++;
		s[k] = malloc((q + 1) * sizeof(char));
		if (!s[q])
		{
			for (q = 0; q < k; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < q; w++)
			s[k][w] = str[y++];
		s[k][w] = 0;
	}
	s[k] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @f: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char f)
{
	int y, k, q, w, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (y = 0; str[y] != '\0'; y++)
		if ((str[y] != f && str[y + 1] == f) ||
				(str[y] != f && !str[y + 1]) || str[y + 1] == f)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, k = 0; k < numwords; k++)
	{
		while (str[y] == f && str[y] != f)
			y++;
		q = 0;
		while (str[y + q] != f && str[y + q] && str[y + q] != f)
			q++;
		s[k] = malloc((q + 1) * sizeof(char));
		if (!s[k])
		{
			for (q = 0; q < k; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (w = 0; w < q; w++)
			s[k][w] = str[y++];
		s[k][w] = 0;
	}
	s[k] = NULL;
	return (s);
}
