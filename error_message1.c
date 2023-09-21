#include "shell.h"

/**
 * env_error - Creates an error message for shellby_env errors.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *env_error(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	argb--;
	ren = _strlen(name) + _strlen(histo_str) + _strlen(argb[0]) + 45;
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
	_strcat(erra, ": Unable to add/remove from environment\n");

	free(histo_str);
	return (erra);
}

/**
 * error1 - Creates an error message for shellby_alias errors.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error1(char **argb)
{
	char *erra;
	int ren;

	ren = _strlen(name) + _strlen(argb[0]) + 13;
	erra = malloc(sizeof(char) * (ren + 1));
	if (!erra)
		return (NULL);

	_strcpy(erra, "alias: ");
	_strcat(erra, argb[0]);
	_strcat(erra, " not found\n");

	return (erra);
}

/**
 * exiterror_2 - Creates an error message for shellby_exit errors.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *exiterror_2(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argb[0]) + 27;
	erra = malloc(sizeof(char) * (ren + 1));
	if (!erra)
	{
		free(histo_str);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histo_str);
	_strcat(erra, ": exit: Illegal number: ");
	_strcat(erra, argb[0]);
	_strcat(erra, "\n");

	free(histo_str);
	return (erra);
}

/**
 * cderror_2 - Creates an error message for shellby_cd errors.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *cderror_2(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	if (argb[0][0] == '-')
		argb[0][2] = '\0';
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
	if (argb[0][0] == '-')
		_strcat(erra, ": cd: Illegal option ");
	else
		_strcat(erra, ": cd: can't cd to ");
	_strcat(erra, argb[0]);
	_strcat(erra, "\n");

	free(histo_str);
	return (erra);
}

/**
 * syntaxerror_2 - Creates an error message for syntax errors.
 * @argb: An array of arguments passed to the command.
 * Return: The error string.
 */
char *syntaxerror_2(char **argb)
{
	char *erra, *histo_str;
	int ren;

	histo_str = _atoi(hist);
	if (!histo_str)
		return (NULL);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(argb[0]) + 33;
	erra = malloc(sizeof(char) * (ren + 1));
	if (!erra)
	{
		free(histo_str);
		return (NULL);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histo_str);
	_strcat(erra, ": Syntax error: \"");
	_strcat(erra, argb[0]);
	_strcat(erra, "\" unexpected\n");

	free(histo_str);
	return (erra);
}
