#include "shell.h"
/**
 * _pputs - prints an input string
 * @srt: string to be printed
 * Return: return nothing
 */
void _pputs(char *srt)
{
	int y = 0;

	if (!srt)
		return;
	while (srt[y] != '\0')
	{
		_pputchar(srt[y]);
		y++;
	}
}
/**
 * _pputchar - it writes the character c
 * @c: the character to print
 * Return:1 on success
 */
int _pputchar(char c)
{
	static int y;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(2, buff, y);
		y = 0;
	}
	if (c != BUF_FLUSH)
		buf[y++] = c;
	return (1);
}
/**
 * _putpd - writes the character c to given pd
 * @c: the character
 * @pd: The filedescriptor
 * Return: 1 on success
 */
int _putpd(char c, int pd)
{
	static int y;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(pd, buff, y);
		y = 0;
	}
	if (c != BUF_FLUSH)
		buff[y++] = c;
	return (1);
}
/**
 * _putspd - prints an input string
 * @pd: filedescriptor
 * Return: returns number
 */
int _putspd(char *srt int pd)
{
	int y = 0;

	if (!srt)
		return (0);
	while (*srt)
	{
		y += _putpd(*srt++, pd);
	}
	return (y);
}
