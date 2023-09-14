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
		info->cmd_puf_type = CMD_OR;
	}
	else if (puf[j] == '&' && puf[j + 1] == '&')
	{
		puf[j] = 0;
		k++;
		info->cmd_puf_type = CMD_AND;
	}
	else if (puf[j] == ';') /* found end of this command */
	{
		puf[j] = 0; /* replace semicolon with null */
		info->cmd_puf_type = CMD_CHAIN;
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

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			puf[y] = 0;
			k = ren;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
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
		done = done_start_with(info->alias, info->argv[0], '=');
		if (!done)
			return (0);
		free(info->argv[0]);
		a = _strchr(node->str, '=');
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
			vars_replace(&(info->argv[y]),
					strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			vars_replace(&(info->argv[y]),
					strdup(int convert_number(getpid(), 10, 0)));
			continue;
		}
		done = done_start_with(info->env, &info->argv[y][1], '=');
		if (done)
		{
			replace_var(&(info->argv[y]),
					strdup(_strchr(done->srt, '=') + 1));
			continue;
		}
		replace_var(&info->argv[y], strdup(""));
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
