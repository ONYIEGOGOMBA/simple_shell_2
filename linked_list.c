#include "shell.h"
/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @herd: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **herd, char *name, char *value)
{
	alias_t *node_new = malloc(sizeof(alias_t));
	alias_t *last;

	if (!node_new)
		return (NULL);

	node_new->next = NULL;
	node_new->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!node_new->name)
	{
		free(node_new);
		return (NULL);
	}
	node_new->value = value;
	_strcpy(node_new->name, name);

	if (*herd)
	{
		last = *herd;
		while (last->next != NULL)
			last = last->next;
		last->next = node_new;
	}
	else
		*herd = node_new;

	return (node_new);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @herd: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **herd, char *dir)
{
	list_t *node_new = malloc(sizeof(list_t));
	list_t *lass;

	if (!node_new)
		return (NULL);

	node_new->dir = dir;
	node_new->next = NULL;

	if (*herd)
	{
		lass = *herd;
		while (lass->next != NULL)
			lass = lass->next;
		lass->next = node_new;
	}
	else
		*herd = node_new;

	return (node_new);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @herd: THe head of the alias_t list.
 */
void free_alias_list(alias_t *herd)
{
	alias_t *next;

	while (herd)
	{
		next = herd->next;
		free(herd->name);
		free(herd->value);
		free(herd);
		herd = next;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @herd: The head of the list_t list.
 */
void free_list(list_t *herd)
{
	list_t *next;

	while (herd)
	{
		next = herd->next;
		free(herd->dir);
		free(herd);
		herd = next;
	}
}
