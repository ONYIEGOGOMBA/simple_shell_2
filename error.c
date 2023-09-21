#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int ren_num(int num)
{
	unsigned int num_1;
	int ren = 1;

	if (num < 0)
	{
		ren++;
		num_1 = num * -1;
	}
	else
	{
		num_1 = num;
	}
	while (num_1 > 9)
	{
		ren++;
		num_1 /= 10;
	}

	return (ren);
}

/**
 * _atoi - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_atoi(int num)
{
	char *buff;
	int ren = ren_num(num);
	unsigned int num_1;

	buff = malloc(sizeof(char) * (ren + 1));
	if (!buff)
		return (NULL);

	buff[ren] = '\0';

	if (num < 0)
	{
		num_1 = num * -1;
		buff[0] = '-';
	}
	else
	{
		num_1 = num;
	}

	ren--;
	do {
		buff[ren] = (num_1 % 10) + '0';
		num_1 /= 10;
		ren--;
	} while (num_1 > 0);

	return (buff);
}


/**
 * creates_error - Writes a custom error message to stderr.
 * @argb: An array of arguments.
 * @err: The error value.
 * Return: The error value.
 */
int creates_error(char **argb, int err)
{
	char *erra;

	switch (err)
	{
	case -1:
		erra = env_error(argb);
		break;
	case 1:
		erra = error1(argb);
		break;
	case 2:
		if (*(argb[0]) == 'e')
			erra = exiterror_2(++argb);
		else if (argb[0][0] == ';' || argb[0][0] == '&' || argb[0][0] == '|')
			erra = syntaxerror_2(argb);
		else
			erra = cderror_2(argb);
		break;
	case 126:
		erra = error_126(argb);
		break;
	case 127:
		erra = error_127(argb);
		break;
	}
	write(STDERR_FILENO, erra, _strlen(erra));

	if (erra)
		free(erra);
	return (err);

}
