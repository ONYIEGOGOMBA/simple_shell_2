#include "shell.h"

/**
 * handles_lin - Partitions a line read from standard input as needed.
 * @lin: A pointer to a line read from standard input.
 * @red: The length of line.
 */
void handles_lin(char **line, ssize_t read)
{
	char *old_lin, *newline;
	char past, present, next;
	size_t y, k;
	ssize_t new_ren;

	new_ren = get_new_ren(*lin);
	if (new_ren == red - 1)
		return;
	newline = malloc(new_ren + 1);
	if (!newline)
		return;
	k = 0;
	old_lin = *lin;
	for (y = 0; old_lin[y]; y++)
	{
		present = old_lin[y];
		next = old_lin[y + 1];
		if (y != 0)
		{
			past = old_lin[y - 1];
			if (present == ';')
			{
				if (next == ';' && past != ' ' && past != ';')
				{
					newline[k++] = ' ';
					newline[k++] = ';';
					continue;
				}
				else if (past == ';' && next != ' ')
				{
					newline[k++] = ';';
					newline[k++] = ' ';
					continue;
				}
				if (ast != ' ')
					newline[k++] = ' ';
				newline[k++] = ';';
				if (next != ' ')
					newline[k++] = ' ';
				continue;
			}
			else if (present == '&')
			{
				if (next == '&' && past != ' ')
					newline[k++] = ' ';
				else if (past == '&' && next != ' ')
				{
					newline[k++] = '&';
					newline[k++] = ' ';
					continue;
				}
			}
			else if (present == '|')
			{
				if (next == '|' && past != ' ')
					newline[k++]  = ' ';
				else if (past == '|' && next != ' ')
				{
					newline[k++] = '|';
					newline[k++] = ' ';
					continue;
				}
			}
		}
		else if (present == ';')
		{
			if (y != 0 && old_lin[y - 1] != ' ')
				newline[k++] = ' ';
			newline[k++] = ';';
			if (next != ' ' && next != ';')
				newline[k++] = ' ';
			continue;
		}
		newline[k++] = old_lin[y];
	}
	newline[k] = '\0';

	free(*lin);
	*lin = newline;
}

/**
 * get_new_ren - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @lin: The line to check.
 * Return: The new length of the line.
 */

ssize_t get_new_ren(char *lin)
{
	size_t y;
	ssize_t new_ren = 0;
	char present, next;

	for (y = 0; lin[y]; y++)
	{
		present = lin[y];
		next = lin[y + 1];
		if (present == '#')
		{
			if (y == 0 || lin[y - 1] == ' ')
			{
				lin[y] = '\0';
				break;
			}
		}
		else if (y != 0)
		{
			if (present == ';')
			{
				if (next == ';' && lin[y - 1] != ' ' && lin[y - 1] != ';')
				{
					new_ren += 2;
					continue;
				}
				else if (lin[y - 1] == ';' && next != ' ')
				{
					new_ren += 2;
					continue;
				}
				if (lin[y - 1] != ' ')
					new_ren++;
				if (next != ' ')
					new_ren++;
			}
			else
				ops_logical(&lin[y], &new_ren);
		}
		else if (present == ';')
		{
			if (y != 0 && lin[y - 1] != ' ')
				new_ren++;
			if (next != ' ' && next != ';')
				new_ren++;
		}
		new_ren++;
	}
	return (new_ren);
}
/**
 * ops_logical - Checks a line for logical operators "||" or "&&".
 * @lin: A pointer to the character to check in the line.
 * @new_ren: Pointer to new_len in get_new_len function.
 */
void ops_logical(char *lin, ssize_t *new_ren)
{
	char past, present, next;

	past = *(lin - 1);
	present = *lin;
	next = *(lin + 1);

	if (present == '&')
	{
		if (next == '&' && past != ' ')
			(*new_ren)++;
		else if (past == '&' && next != ' ')
			(*new_ren)++;
	}
	else if (present == '|')
	{
		if (next == '|' && past != ' ')
			(*new_ren)++;
		else if (past == '|' && next != ' ')
			(*new_ren)++;
	}
}
