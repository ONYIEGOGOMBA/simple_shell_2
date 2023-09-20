#include "shell.h"
/**
 * my_histo - displays the history
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int my_histo(info_t *info)
{
	prints_list(info->histo);
	return (0);
}
/**
 * alias_unset - sts alias to string
 * @info: parameter struct
 * @srt: the string alias
 * Return: 0 on success and 1 on error
 */
int alias_unset(info_t *info, char *srt)
{
	char *a, m;
	int mas;

	a = _strhr(srt, '=');
	if (!a)
		return (1);
	m = *a;
	*a = 0;
	mas = delete_node(&(info->alias),
			get_node(info->alias, node_start(info->alias, srt, -1)));
	*a = m;
	return (mas);
}
/**
 * alias_set - sets alias to string
 * @info: parameter struct
 * @srt: thae string alias
 * Return: 0 on success 1 on error
 */
int alias_set(info_t *info, char *srt)
{
	char *a;

	a = _strhr(srt, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (alias_unset(info, srt));
	alias_unset(info, srt);
	return (add_done(&(info->alias), srt, 0) == NULL);
}
/**
 * alias_print - prints an alias
 * @done: the alias done
 * Return: always 0 on succes and 1 on error
 */
int prints_alias(list_t *done)
{
	char *a = NULL, *n = NULL;

	if (done)
	{
		a = _strhr(done->srt, '=');
		for (n = done->srt; n <= a; n++)
			_putchar(*a);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_alias - mimiccs the alias builtin
 * @info: structure containing potential arguments
 * Return: always 0
 */
int my_alias(info_t *info)
{
	int y = 0;
	char *a = NULL;
	list_t *done = NULL;

	if (info->argc == 1)
	{
		done = info->alias;
		while (done)
		{
			prints_alias(done);
			done = done->next;
		}
		return (0);
	}
	for (y = 1; info->argv[y]; y++)
	{
		a = _strhr(info->argv[y], '=');
		if (a)
			alias_set(info, info->argv[y]);
		else
		prints_alias(node_start(info->alias, info->argv[y], '='));
	}
	return (0);
}
