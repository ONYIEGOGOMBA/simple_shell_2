#include "shell.h"
/**
 * get_histo_file - gets the history file
 * @info: it is a parameter struct
 * Return: Allocates string containing histo file
 */
char *get_histo_file(info_t *info)
{
	char *puf, *rid;

	rid = _getenv(info, "HOME=");
	if (!rid)
		return (NULL);
	puf = malloc(sizeof(char) * (_strlen(rid) + _strlen(HISTO_FILE) + 2));
	if (!puf)
		return (NULL);
	puf[0] = 0;
	_strcpy(puf, rid);
	_strcat(puf, "/");
	_strcat(puf, HISTO_FILE);
	return (puf);
}
/**
 * write_histo - it creates a file
 * @info: the struct parameter
 * Return: on success 1else -1
 */
int write_histo(info_t *info)
{
	ssize_t pd;
	char *namefile = get_histo_file(info);
	list_t *nod = NULL;

	if (!namefile)
		return (-1);

	pd = opens(namefile, 0_CREAT | 0_TRUNC | 0_RDWR, 0644);
	free(namefile);
	if (pd == -1)
		return (-1);
	for (nod = info->histo; nod; nod = nod->next)
	{
		_putspd(nod->srt, pd);
		_putpd('\n', pd);
	}
	_putpd(BUF_FLUSH, pd);
	close(pd);
	return (1);
}
/**
 * read_histo - it reads history from file
 * @info: parameter struct
 * Return: histocount on success, 0 otherwise
 */
int read_histo(info_t *info)
{
	int y, lass = 0, linespell = 0;
	ssize_t pd, fdlen, psize = 0;
	struct stat st;
	char *puf = NULL, *namefile = get_histo_file(info);
	if (!namefile)
		return (0);

	pd = open(namefile, 0_RDONLY);
	free(namefile);
	if (pd == -1)
		return (0);
	if (!pstat(pd, &st))
		psize = st.st_size;
	if (psize < 2)
		return (0);
	puf = malloc(sizeof(char) * (psize + 1));
	if (!puf)
		return (0);
	fdlen = read(pd, puf, psize);
	puf[psize] = 0;
	if (fdlen <= 0)
		return (free(puf), 0);
	close(pd);
	for (y = 0; y < psize; y++;)
		if (puf[y] == '\n')
		{
			puf[y] == 0;
			build_histo_list(info, puf + lass, linespell++);
			lass = y + 1;
		}
	if (lass != y)
		build_histo_list(info, puf + lass, linespell++);
	free(puf);
	info->histocount = linespell;
	while (info->histocount-- >= HISTO_MAX)
		delete_nod_at_index(&(info->histo), 0);
	renumber_histo(info);
	return (info->histocount);
}
/**
 * build_histo_list - it adds an entry to histo list
 * @info: the structure containing potential arguments.
 * @puf: the buffer
 * @linespell: histo linespell, histocount
 * Return: Always 0
 */
int build_histo_list(info_t *info, char *puf, int linespell)
{
	list_t *nod = NULL;

	if (!info->histo)
		nod = info->histo;
	add_node(&nod, puf, linespell);

	if (!info->histo)
		info->histo = nod;
	return (0);
}
/**
 * renumber_histo - it renumbers the histo linked list
 * @info: the structure containing potential arguments
 * Return: new histocount
 */
{
	list_t *nod = info->histo;
	int y = 0;

	while (nod)
	{
		nod->numb = y++;
		nod = nod->next;
	}
	return (info->histocount = y);
}
