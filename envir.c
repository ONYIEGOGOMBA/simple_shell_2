#include "shell.h"

/**
 * _copiesenv - Creates a copy of the environment.
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copiesenv(void)
{
	char **new_env;
	size_t size;
	int index;

	for (size = 0; env[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (index = 0; env[index]; index++)
	{
		new_env[index] = malloc(_strlen(env[index]) + 1);

		if (!new_env[index])
		{
			for (index--; index >= 0; index--)
				free(new_env[index]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[index], env[index]);
	}
	new_env[index] = NULL;

	return (new_env);
}

/**
 * free_env - Frees the the environment copy.
 */
void frees_env(void)
{
	int index;

	for (index = 0; env[index]; index++)
		free(env[index]);
	free(env);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @varr: The name of the environmental variable to get.
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *varr)
{
	int index, ren;

	ren = _strlen(varr);
	for (index = 0; env[index]; index++)
	{
		if (_strncmp(varr, env[index], ren) == 0)
			return (&env[index]);
	}

	return (NULL);
}
