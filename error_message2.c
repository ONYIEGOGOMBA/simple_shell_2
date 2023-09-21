#include "shell.h"

/**
 * 126_error - Creates an error message for permission denied failures.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *126_error(char **argd)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(histo);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argd[0]) + 24;
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
	_strcat(erra, argd[0]);
	_strcat(erra, ": Permission denied\n");

	free(histo_str);
	return (erra);
}

/**
 * 127_error - Creates an error message for command not found failures.
 * @argd: An array of arguments passed to the command.
 * Return: The error string.
 */
char *127_error(char **argd)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(histo);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argd[0]) + 16;
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
	_strcat(erra, argd[0]);
	_strcat(erra, ": not found\n");

	free(histo_str);
	return (erra);
}
