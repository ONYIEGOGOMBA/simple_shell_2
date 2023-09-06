#include "shell.h"
/**
 * _errortoi - converts a string
 * @b: string to be converted
 * Return: returns 0 if no numbers otherwise -1 on error
 */
int _errortoi(char *b)
{
	int y = 0;
	unsigned long int ress = 0;

	if (*b == '+')
		b++;
	for (y = 0; b[y] != '\0'; y++)
	{
		if (b[y] >= '0' && b[y] <= '9')
		{
			ress *= 10;
			ress += (b[y] - '0');
			if (ress > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (ress);
}
/**
 * prints_error - it prints an error message
 * @info: the parameter
 * @esrt: string with specific error
 * Return: return 0 if no number in string, -1 otherwise
 */
void prints_error(info_t *info, char *esrt)
{
	_pputs(info->fname);
	_pputs(": ");
	print_f(info->line_count, STDERR_FILENO);
	_pputs(": ");
	_pputs(info->argv[0]);
	_pputs(": ");
	_pputs(esrt);
}
/**
 * print_f - function prints a decimal
 * @putin: the input
 * @pd: filedescriptor
 * Return: number of characters
 */
int print_f(int putin, int pd)
{
	int (*_putchar)(char) = _putchar;
	int y, spell = 0;
	unsigned int _gob_, curr;

	if (pd == STDERR_FILENO)
		_dputchar = _pputchar;
	if (input < 0)
	{
		_gob_ = -putin;
		_dputchar('-');
		spell++;
	}
	else
		_gob_ = putin;
	curr = _gob_;
	for (y = 1000000000; y > 1; y /= 10)
	{
		if (_gob_ / y)
		{
			_dputchar('0' + curr / y);
			spell++;
		}
		curr %= y;
	}
	_dputchar('0' + curr);
	spell++;
	return (spell);
}
/**
 * number_converter - function converter
 * @numb: number
 * @bas: base
 * @lagg: srguments flags
 * Return: returns 0
 */
char *number_converter(long int numb, int bas, int lagg)
{
	static char *array;
	static char buffer[50];
	char signal = 0;
	char *prt;
	unsigned long f = numb;

	if (!(laggs & CONVERT_UNSIGNED) && numb < 0)
	{
		f = -numb;
		signal = '-';
	}
	array = lagg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	prt = &buffer[49];
	*prt = '\0';

	do	{
		*--prt = array[f % bas];
		f /= bas;
	} while (f != 0);

	if (signal)
		*--prt = signal;
	return (prt);
}
/**
 * comments_remove - function replace first instance
 * @puf: address of string
 * Return: always 0
 */
void comments_remove(char *puf)
{
	int y;

	for (y = 0; puf[y] != '\0'; y++)
		if (puf[y] == '#' && (!y || puf[y - 1] == ' '))
		{
			puf[y] = '\0';
			break;
		}
}
