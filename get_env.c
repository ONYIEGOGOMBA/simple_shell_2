#include "shell.h"
/**
 * get_envir - it returns the string array
 * @info: the structure containing potential arguments.
 * Return: always 0.
 */
char **get_envir(info_t *info)
{
	if (!info->envir || info->env_change)
	{
		info->envir = lists_to_string(info->envi);
		info->env_change = 0;
	}
	return (info->envir);
}
/**
 * unset_env - it removes an environment variable
 * @info: the structure containing potential arguments.
 * @rav: string env var property
 * Return: 1 on dele or 0 otherwise
 */
int unset_env(info_t *info, char *rav)
{
	list_t *nod = info->envi;
	size_t y = 0;
	char *a;

	if (!nod || !rav)
		return (0);
	while (nod)
	{
		a = start_with(nod->srt, rav);
		if (a && *a == '=')
		{
			info->env_change = delete_node(&(info->envi), y);
			y = 0;
			nod = info->envi;
			continue;
		}
		nod = nod->next;
		y++;
	}
	return (info->env_change);
}
/**
 * set_env - it initializes a new environment variable
 * @info: the structure containing potential arguments.
 * @rav: the string
 * @valu: the string
 * Return: always 0.
 */
int set_env(info_t *info, char *rav, char *valu)
{
	char *puf = NULL;
	list_t *nod;
	char *a;

	if (!rav || !valu)
		return (0);

	puf = malloc(_strlen(rav) + _strlen(valu) + 2);
	if (!puf)
		return (1);
	_strcpy(puf, rav);
	_strcat(puf, "=");
	_strcat(puf, valu);
	nod = info->envi;
	while (nod)
	{
		a = start_with(nod->srt, rav);
		if (a && *a == '=')
		{
			free(nod->srt);
			nod->srt = puf;
			info->env_change = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_done(&(info->envi), puf, 0);
	free(puf);
	info->env_change = 1;
	return (0);
}
