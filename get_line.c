#include "shell.h"
/**
 * _reallocate - Reallocates a memory block using malloc and free.
 * @rpt: A pointer to the memory previously allocated.
 * @oldsize: The size in bytes of the allocated space for ptr.
 * @newsize: The size in bytes for the new memory block.
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_reallocate(void *rpt, unsigned int oldsize, unsigned int newsize)
{
	void *nem;
	char *rpt_copy, *fill;
	unsigned int index;

	if (newsize == oldsize)
		return (rpt);

	if (rpt == NULL)
	{
		nem = malloc(newsize);
		if (nem == NULL)
			return (NULL);

		return (nem);
	}

	if (newsize == 0 && rpt != NULL)
	{
		free(rpt);
		return (NULL);
	}

	rpt_copy = rpt;
	nem = malloc(sizeof(*rpt_copy) * newsize);
	if (nem == NULL)
	{
		free(rpt);
		return (NULL);
	}

	fill = nem;

	for (index = 0; index < oldsize && index < newsize; index++)
		fill[index] = *rpt_copy++;

	free(rpt);
	return (nem);
}

/**
 * assign_line - Reassigns the lineptr variable for _getline.
 * @linerpt: A buffer to store an input string.
 * @f: The size of lineptr.
 * @buff: The string to assign to lineptr.
 * @s: The size of buffer.
 */
void assign_line(char **linerpt, size_t *f, char *buff, size_t s)
{
	if (*linerpt == NULL)
	{
		if (s > 120)
			*f = s;
		else
			*f = 120;
		*linerpt = buff;
	}
	else if (*f < s)
	{
		if (s > 120)
			*f = s;
		else
			*f = 120;
		*linerpt = buff;
	}
	else
	{
		_strcpy(*linerpt, buff);
		free(buff);
	}
}

/**
 * _getline - Reads input from a stream.
 * @linerpt: A buffer to store the input.
 * @f: The size of lineptr.
 * @steam: The stream to read from.
 * Return: The number of bytes read.
 */
ssize_t _getline(char **linerpt, size_t *f, FILE *steam)
{
	static ssize_t inputs;
	ssize_t rett;
	char b = 'x', *buff;
	int r;

	if (inputs == 0)
		fflush(steam);
	else
		return (-1);
	inputs = 0;

	buffers = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (b != '\n')
	{
		r = read(STDIN_FILENO, &b, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && inputs != 0)
		{
			inputs++;
			break;
		}

		if (inputs >= 120)
			buff = _reallocate(buff, inputs, inputs + 1);

		buff[inputs] = b;
		inputs++;
	}
	buff[inputs] = '\0';

	assign_line(linerpt, f, buff, inputs);

	rett = inputs;
	if (r != 0)
		inputs = 0;
	return (rett);
}
