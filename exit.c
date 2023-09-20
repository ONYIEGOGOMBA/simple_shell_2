#include "shell.h"
/**
 * _strcpy - it copies a string
 * @dess: destination string
 * @scr: source string
 * @f: amount of characters
 * Return: concatenanted string
 */
char *_strmcpy(char *dess, char *scr, int f)
{
	int y, k;
	char *b = dess;

	y = 0;
	while (scr[y] != '\0' && y < f - 1)
	{
		dess[y] = scr[y];
		y++;
	}
	if (y < f)
	{
		k = y;
		while (k < f)
		{
			dess[k] = '\0';
			k++;
		}
	}
	return (b);
}
/**
 * _strcat - concatenates string
 * @dess: first string
 * @scr: second string
 * @f: amount of bytes
 * Return: concatenated string
 */
char *_strmcat(char *dess, char *scr, int f)
{
	int y, k;
	char *b = dess;

	y = 0;
	k = 0;
	while (dess[y] != '\0')
		y++;
	while (scr[k] != '\0' && k < f)
	{
		dess[y] = scr[k];
		y++;
		k++;
	}
	if (k < f)
		dess[y] = '\0';
	return (b);
}
/**
 * _strhr - it locates a character
 * @b: string to be passed
 * @o: character to llok for
 * Return: a pointer
 */
char *_strhr(char *b, char o)
{
	do {
		if (*b == o)
			return (b);
	} while (*b++ != '\0');
	return (NULL);
}
