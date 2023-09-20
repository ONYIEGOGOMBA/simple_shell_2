#include "shell.h"

/**
 * chain_is - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @puf: the char puffer
 * @a: address of current position in puf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_is(info_t *info, char *puf, size_t *a)
{
	size_t k = *a;

	if (puf[k] == '|' && puf[k + 1] == '|')
	{
		puf[k] = 0;
		k++;
		info->cmd_puf_type = CMD_ORR;
	}
	else if (puf[k] == '&' && puf[k + 1] == '&')
	{
		puf[k] = 0;
		k++;
		info->cmd_puf_type = CMD_ANDD;
	}
	else if (puf[k] == ';')
	{
		puf[k] = 0;
		info->cmd_puf_type = CMD_CHAINS;
	}
	else
		return (0);
	*a = k;
	return (1);
}

/**
 * chain_check - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @puf: the char puffer
 * @a: address of current position in puf
 * @y: starting position in puf
 * @ren: length of puf
 *
 * Return: Void
 */
void chain_check(info_t *info, char *puf, size_t *a, size_t y, size_t ren)
{
	size_t k = *a;

	if (info->cmd_puf_type == CMD_ANDD)
	{
		if (info->status)
		{
			puf[y] = 0;
			k = ren;
		}
	}
	if (info->cmd_puf_type == CMD_ORR)
	{
		if (!info->status)
		{
			puf[y] = 0;
			k = ren;
		}
	}
	*a = k;
}

/**
 * alias_replace - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *info)
{
	int y;
	list_t *done;
	char *a;

	for (y = 0; y < 10; y++)
	{
		done = node_start(info->alias, info->argv[0], '=');
		if (!done)
			return (0);
		free(info->argv[0]);
		a = _strhr(done->srt, '=');
		if (!a)
			return (0);
		a = strdup(a + 1);
		if (!a)
			return (0);
		info->argv[0] = a;
	}
	return (1);
}

/**
 * vars_replace - replaces vars in the tokenized string
 * @info_t - a parameter
 * @*info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *info)
{
	int y = 0;

	list_t *done;

	for (y = 0; info->argv[y]; y++)
	{
		if (info->argv[y][0] != '$' || !info->argv[y][1])
			continue;
		if (!_strcmp(info->argv[y], "$?"))
		{
			string_replace(&(info->argv[y]),
					strdup(number_converter(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			string_replace(&(info->argv[y]),
					strdup(number_converter(getpid(), 10, 0)));
			continue;
		}
		done = node_start(info->env, &info->argv[y][1], '=');
		if (done)
		{
			string_replace(&(info->argv[y]),
					strdup(_strhr(done->srt, '=') + 1));
			continue;
		}
		string_replace(&info->argv[y], strdup(""));
	}
	return (0);
}

/**
 * string_replace - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
