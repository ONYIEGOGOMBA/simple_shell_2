#include "shell.h"

/**
 * list_lens - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
ssize_t list_lens(const list_t *h)
{
	ssize_t y = 0;

	while (h)
	{
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * lists_to_string - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **lists_to_string(list_t *h)
{
	list_t *done = h;
	ssize_t y = list_lens(h), k;
	char **strs;
	char *str;

	if (!h || !y)
		return (NULL);
	strs = malloc(sizeof(char *) * (y + 1));
	if (!strs)
		return (NULL);
	for (y = 0; done; done = done->next, y++)
	{
		str = malloc(_strlen(done->srt) + 1);
		if (!str)
		{
			for (k = 0; k < y; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, done->srt);
		strs[y] = str;
	}
	strs[y] = NULL;
	return (strs);
}


/**
 * list_print - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
ssize_t list_print(const list_t *h)
{

	size_t y = 0;

	while (h)
	{
		_puts(number_converter(h->bam, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->srt ? h->srt : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * done_start_with - returns node whose strinet number
 e starts with prefix
 * @done: pointer to list head
 * @prefix: string to match
 * @o: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *done_start_with(list_t *done, char *prefix, char o)
{

	char *a = NULL;

	while (done)
	{
		a = start_with(done->srt, prefix);
		if (a && ((o == -1) || (*a == o)))
			return (done);
		done = done->next;
	}
	return (NULL);
}

/**
 * gets_done_index - gets the index of a node
 * @h: pointer to list head
 * @done: pointer to the node
 *
 * Return: index of node or -1
 */

size_t gets_done_index(list_t *h, list_t *done)
{
	size_t y = 0;

	while (h)
	{
		if (h == done)
			return (y);
		h = h->next;
		y++;
	}
	return (-1);
}
