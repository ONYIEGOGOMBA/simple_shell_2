#include "shell.h"

/**
 * env_shell - Prints the current environment.
 * @argb: An array of arguments passed to the shell.
 * @infront: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
int env_shell(char **argb, char __attribute__((__unused__)) **infront)
{
	int index;
	char gom = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &gom, 1);
	}

	(void)argb;
	return (0);
}

/**
 * setenv_shell - Changes or adds an environmental variable to the PATH.
 * @argb: An array of arguments passed to the shell.
 * @infront: A double pointer to the beginning of argb.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int setenv_shell(char **argb, char __attribute__((__unused__)) **infront)
{
	char **var_env = NULL, **new_env, *newvalue;
	size_t size;
	int index;

	if (!argb[0] || !argb[1])
		return (creates_error(argb, -1));

	newvalue = malloc(_strlen(argb[0]) + 1 + _strlen(argb[1]) + 1);
	if (!newvalue)
		return (creates_error(argb, -1));
	_strcpy(newvalue, argb[0]);
	_strcat(newvalue, "=");
	_strcat(newvalue, argb[1]);

	var_env = _getenv(argb[0]);
	if (var_env)
	{
		free(*var_env);
		*var_env = newvalue;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(newvalue);
		return (creates_error(argb, -1));
	}

	for (index = 0; environ[index]; index++)
		new_env[index] = environ[index];

	free(environ);
	environ = new_env;
	environ[index] = newvalue;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * unsetenv_shell - Deletes an environmental variable from the PATH.
 * @argb: An array of arguments passed to the shell.
 * @infront: A double pointer to the beginning of argb.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unsetenv_shell(char **argb, char __attribute__((__unused__)) **infront)
{
	char **var_env, **new_env;
	size_t size;
	int index, index_2;

	if (!argb[0])
		return (creates_error(argb, -1));
	var_env = _getenv(argb[0]);
	if (!var_env)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (creates_error(argb, -1));

	for (index = 0, index_2 = 0; environ[index]; index++)
	{
		if (*var_env == environ[index])
		{
			free(*var_env);
			continue;
		}
		new_env[index_2] = environ[index];
		index_2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}
