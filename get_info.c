#include "shell.h"
/**
 * info_clear - it initializes info_t struct
 * @info: the struct address
 */
void info_clear(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->paths = NULL;
	info->argc = 0;
}
/**
 * info_set - initializes info_t struct
 * @info: the struct address
 * @va: the argument vector
 */
void sets_info(info_t *info, char **va)
{
	int y = 0;

	info->fname = va[0];
	if (info->arg)
	{
		info->argv = strwot(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (y = 0; info->argv && info->argv[y]; y++)
			;
		info->argc = y;

		alias_replace(info);
		vars_replace(info);
	}
}
/**
 * info_free - it frees info_t
 * @info: the struct address
 * @both: is true if all fields are freed
 */
void frees_info(info_t *info, int both)
{
	pfree(info->argv);
	info->argv = NULL;
	info->paths = NULL;
	if (both)
	{
		if (!info->cmd_puf)
			free(info->arg);
		if (info->envi)
			frees_lists(&(info->envi));
		if (info->histo)
			frees_lists(&(info->histo));
		if (info->alias)
			frees_lists(&(info->alias));
		pfree(info->envir);
		info->envir = NULL;
		cfree((void **)info->cmd_puf);
		if (info->readpd > 2)
			close(info->readpd);
		_putchar(BUF_FLUSH);
	}
}
