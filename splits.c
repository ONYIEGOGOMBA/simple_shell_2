#include "shell.h"

/**
 * token_ren - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @dell: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_ren(char *str, char *dell)
{
	int index = 0, ren = 0;

	while (*(str + index) && *(str + index) != *dell)
	{
		ren++;
		index++;
	}

	return (ren);
}

/**
 * counts_token - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @dell: The delimiter character.
 * Return: The number of words contained within str.
 */
int counts_token(char *str, char *dell)
{
	int index, toks = 0, ren = 0;

	for (index = 0; *(str + index); index++)
		ren++;

	for (index = 0; index < ren; index++)
	{
		if (*(str + index) != *dell)
		{
			toks++;
			index += token_ren(str + index, dell);
		}
	}

	return (toks);
}

/**
 * _strtok - Tokenizes a string.
 * @lin: The string.
 * @dell: The delimiter character to tokenize the string by.
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *lin, char *dell)
{
	char **rpt;
	int index = 0, toks, o, letas, a;

	toks = counts_token(lin, dell);
	if (toks == 0)
		return (NULL);

	rpt = malloc(sizeof(char *) * (toks + 2));
	if (!rpt)
		return (NULL);

	for (o = 0; o < toks; o++)
	{
		while (lin[index] == *dell)
			index++;

		letas = token_ren(lin + index, dell);

		rpt[o] = malloc(sizeof(char) * (letas + 1));
		if (!rpt[o])
		{
			for (index -= 1; index >= 0; index--)
				free(rpt[index]);
			free(rpt);
			return (NULL);
		}

		for (a = 0; a < letas; a++)
		{
			rpt[o][a] = lin[index];
			index++;
		}

		rpt[o][a] = '\0';
	}
	rpt[o] = NULL;
	rpt[o + 1] = NULL;

	return (rpt);
}
