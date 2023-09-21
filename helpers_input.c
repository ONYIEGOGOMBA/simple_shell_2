#include "shell.h"

/**
 * gets_argb - Gets a command from standard input.
 * @lin: A buffer to store the command.
 * @exec_ret: The return value of the last executed command.
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *gets_argb char *line, int *exe_ret)
{
	size_t f = 0;
	ssize_t red;
	char *promp = "$ ";

	if (lin)
		free(lin);

	red = _getline(&lin, &f, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (red == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, promp, 2);
		return (gets_argb(lin, exec_ret));
	}

	lin[read - 1] = '\0';
	var_replacement(&lin, exec_ret);
	handles_lin(&lin, re);

	return (lin);
}

/**
 * calls_argb - Partitions operators from commands and calls them.
 * @argb: An array of arguments.
 * @infront: A double pointer to the beginning of args.
 * @exec_ret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int calls_argb(char **argb, char **infront, int *exec_ret)
{
	int rett, index;

	if (!argb[0])
		return (*exec_ret);
	for (index = 0; argb[index]; index++)
	{
		if (_strncmp(argb[index], "||", 2) == 0)
		{
			free(argb[index]);
			argb[index] = NULL;
			argb = replaces_aliases(args);
			ret = runs_argb(argb, infront, exec_ret);
			if (*exec_ret != 0)
			{
				argb = &argb[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(argb[index]);
				return (rett);
			}
		}
		else if (_strncmp(argb[index], "&&", 2) == 0)
		{
			free(argb[index]);
			argb[index] = NULL;
			argb = replaces_aliases(argb);
			rett = runs_argb(argb, infront, exec_ret);
			if (*exec_ret == 0)
			{
				argb = &argb[++index];
				index = 0;
			}
			else
			{
				for (index++; argb[index]; index++)
					free(argb[index]);
				return (rett);
			}
		}
	}
	argb = replaces_aliases(argb);
	rett = runs_argb(argb, infront, exec_ret);
	return (rett);
}

/**
 * runs_argb - Calls the execution of a command.
 * @argb: An array of arguments.
 * @infront: A double pointer to the beginning of args.
 * @exec_ret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int runs_argb(char **argb, char **infront, int *exec_ret)
{
	int rett, y;
	int (*builtin)(char **argb, char **infront);

	builtin = builtin_get(argb[0]);

	if (builtin)
	{
		rett = builtin(argb + 1, infront);
		if (rett != EXIT)
			*exec_ret = rett;
	}
	else
	{
		*exec_ret = execute(argb, infront);
		rett = *exec_ret;
	}

	hist++;

	for (y = 0; argb[y]; y++)
		free(argb[y]);

	return (rett);
}

/**
 * handles_argb - Gets, calls, and runs the execution of a command.
 * @exec_ret: The return value of the parent process' last executed command.
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handles_argb(int *exec_ret)
{
	int rett = 0, index;
	char **argb, *lin = NULL, **infront;

	lin = gets_argb(lin, exec_ret);
	if (!lin)
		return (END_OF_FILE);

	argb = _strtok(lin, " ");
	free(lin);
	if (!argb)
		return (rett);
	if (checks_argb(argb) != 0)
	{
		*exec_ret = 2;
		frees_argb(argb, argb);
		return (*exec_ret);
	}
	infront = argb;

	for (index = 0; argb[index]; index++)
	{
		if (_strncmp(argb[index], ";", 1) == 0)
		{
			free(argb[index]);
			argb[index] = NULL;
			rett = calls_argb(argb, infront, exec_ret);
			argb = &argb[++index];
			index = 0;
		}
	}
	if (argb)
		rett = calls_argb(argb, infront, exec_ret);

	free(infront);
	return (rett);
}

/**
 * checks_argb - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @argb: 2D pointer to tokenized commands and arguments.
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int checks_argb(char **argb)
{
	size_t y;
	char *curr, *necs;

	for (y = 0; argb[y]; y++)
	{
		curr = argb[y];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (y == 0 || curr[1] == ';')
				return (creates_error(&argb[y], 2));
			necs = argb[y + 1];
			if (necs && (necs[0] == ';' || necs[0] == '&' || necs[0] == '|'))
				return (creates_error(&argb[y + 1], 2));
		}
	}
	return (0);
}
