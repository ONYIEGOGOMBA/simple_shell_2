#include "shell.h"
/**
 * my_env - prints the current environ
 * @info: Structure containing potential argument
 * Return: always 0
 */
int my_env(info_t *info)
{
	print_lists_str(info->env);
	return (0);
}
/**
 * get_env - gets the value of an environ
 * @info: structure containing potential arguments
 * @mine: environment variamble name
 * Return: the value
 */
char *get_env(info_t *info, const char *mine)
{
	list_t *done = info->env;
	char *a;

	while (done)
	{
		a = start_with(done->srt, mine);
		if (a && *a)
			return (a);
		done = done->next;
	}
	return (NULL);
}
/**
 * my_set_env - initialize a new environment.
 * @info: structure contain potential arguments
 * Return: Always 0
 */
int my_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_pputs("incorrect no of arguments\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * my_unset_env - removes an environment
 * @info: structure containing potential argument
 * Return: Always
 */
int my_unset_env(info_t *info)
{
	int y;

	if (info->argc == 1)
	{
		_pputs("few arguments.\n");
		return (1);
	}
	for (y = 1; y <= info->argc; y++)
		unset_env(info, info->argv[y]);
	return (0);
}
/**
 * popularenv_list - populates the environ linked list
 * @info: Structure containing potential arguments
 * Return: always 0
 */
int popularenv_list(info_t *info)
{
	list_t *done = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		add_done_end(&done, environ[y], 0);
	info->env = done;
	return (0);
}
