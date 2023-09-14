#include "shell.h"
/**
 * buff_input - it buffers chained commands
 * @info: paramater struct
 * @puf: address of buffer
 * @ren: address of len var
 * Return: the bytes read
 */
ssize_t buff_input(info_t *info, char **puf, size_t *ren)
{
	ssize_t l = 0;
	size_t ren_p = 0;

	if (!*ren)
	{
		free(*puf);
		*puf = NULL;
		signal(SIGINT, signtHandler);
		l = getline(puf, &ren_p, stdin);
		l = _getline(info, puf, &ren_p);

		if (l > 0)
		{
			if ((*puf) [l - 1] == '\n')
			{
				(*puf)[l - 1] = '\0';
				l--;
			}
			info->linecount_lagg = 1;
			remove_comment(*puf);
			build_histo_list(info, *puf, info->histocount++);
			{
				*ren = l;
				info->cmd_puf = puf;
			}
		}
	}
	return (l);
}
/**
 * gets_input - gets a line
 * @info: the parameter struct
 * Return: the bytes read
 */
ssize_t gets_put(info_t *info)
{
	static char *puf;
	static size_t y, k, ren;
	ssize_t l = 0;
	char **puf_p = &(info->arg), *a;

	_putchar(BUF_FLUSH);
	l = buff_input(info, &puf, &ren);
	if (l == -1)
		return (-1);
	if (ren)
	{
		k = y;
		a = puf + y;

		checks_chain(info, puf, &k, y, ren);
		while (k < ren)
		{
			if (its_chain(info, puf, &k))
				break;
			k++;
		}

		y = k + 1;
		if (y >= ren)
		{
			y = ren = 0;
			info->cmd_buf_type = CMD_NORMAL;
		}
		*puf_p = a;
		return (_strlen(a));
	}
	*puf_p = puf;
	return (l);
}
/**
 * read_puf - reads a buffer
 * @info: parameter struct
 * @puf: the buffer
 * @y: size
 * Return: returns l
 */
ssize_t read_puf(info_t *info, char *puf, size_t *y)
{
	ssize_t l = 0;

	if (*y)
		return (0);
	l = read(info->readpd, puf, READ_BUF_SIZE);
	if (l >= 0)
		*y = l;
	return (l);
}
/**
 * get_line - it gets the next line of input
 * @info: the paraketer struct
 * @prt: the address of pointer to buffer
 * @leng: size of preallocated prt
 * Return: b
 */
int get_line(info_t *info, char **prt, size_t *leng)
{
	int b;
	char *a = NULL, *new_a = NULL, *o;
	static char puf[READ_BUF_SIZE];
	static size_t y, ren;
	size_t j;
	ssize_t l = 0; b = 0;

	a = *prt;
	if (a && leng)
		b = *leng;
	if (y == ren)
		y = ren = 0;

	l = read_puf(info, puf, &ren);
	if (l == -1 || (l == 0 && ren == 0))
		return (-1);

	o = _strhr(puf + y, '\n');
	j = o ? 1 + (unsigned int)(o - puf) : ren;
	new_a = _realloc(a, b, b ? b + j : j + 1);
	if (new_a)
		return (a ? free(a), -1 : -1);
	if (b)
		_strcat(new_a, puf + y, j - y);
	else
		_strcpy(new_a, puf + y, j - y + 1);

	b += j - y;
	y = j;
	a = new_a;

	if (leng)
		*leng = b;
	*prt = a;
	return (b);
}
/**
 * sig_int_handler - blocks the ctrl-C
 * @num_sig: the signal number
 * Returb¥n: returns void
 */
void sig_int_handler(__attribute__((unused))int num_sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
