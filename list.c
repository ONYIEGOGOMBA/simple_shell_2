#include "shell.h"

/**
 * add_done - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 * ?I'm willing to help you work on your assignment, consider my bid kindly.
 */
list_t *add_done(list_t **head, const char *str, int numb)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memset((void *)new_head, 0, sizeof(list_t));
	new_head->bam = numb;
	if (str)
	{
		new_head->srt = strdup(str);
		if (!new_head->srt)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_done_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *add_done_end(list_t **head, const char *str, int numb)
{
	list_t *new_done, *done;

	if (!head)
		return (NULL);
	done = *head;
	new_done = malloc(sizeof(list_t));
	if (!new_done)
		return (NULL);
	memset((void *)new_done, 0, sizeof(list_t));
	new_done->bam = numb;
	if (str)
	{
		new_done->srt = strdup(str);
		if (!new_done->srt)
		{
			free(new_done);
			return (NULL);
		}
	}
	if (done)
	{
		while (done->next)
			done = done->next;
		done->next = new_done;
	}
	else
		*head = new_done;
	return (new_done);
}

/**
 * print_lists_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lists_str(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		_puts(h->srt ? h->srt : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * delete_done_at_index - deletes done at given index
 * @head: address of pointer to first node
 * @index: index of done to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_done_at_index(list_t **head, unsigned int index)
{
	list_t *done, *prev_done;
	unsigned int y = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		done = *head;
		*head = (*head)->next;
		free(done->srt);
		free(done);
		return (1);
	}
	done = *head;
	while (done)
	{
		if (y == index)
		{
			prev_done->next = done->next;
			free(done->srt);
			free(done);
			return (1);
		}
		y++;
		prev_done = done;
		done = done->next;
	}
	return (0);
}

/**
 * list_free - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void list_free(list_t **head_ptr)
{
	list_t *done, *next_done, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	done = head;
	while (done)
	{
		next_done = done->next;
		free(done->srt);
		free(done);
		done = next_done;
	}
	*head_ptr = NULL;
}
