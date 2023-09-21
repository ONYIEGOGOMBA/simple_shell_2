#include "shell.h"

/**
 * 126_error - Creates an error message for permission denied failures.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_126(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argb[0]) + 24;
	erra = malloc(sizeof(char) * (ren + 1));
	if (!erra)
	{
		free(histo_str);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histo_str);
	_strcat(erra, ": ");
	_strcat(erra, argb[0]);
	_strcat(erra, ": Permission denied\n");

	free(histo_str);
	return (erra);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_127(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argb[0]) + 16;
	erra = malloc(sizeof(char) * (ren + 1));
	if (!erra)
	{
		free(histo_str);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histo_str);
	_strcat(erra, ": ");
	_strcat(erra, argb[0]);
	_strcat(erra, ": not found\n");

	free(histo_str);
	return (erra);
}
