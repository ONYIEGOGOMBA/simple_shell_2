#include "shell.h"

/**
 * builtin_get - Matches a command with a corresponding
 *               shellby builtin function.
 * @comnd: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*builtin_get(char *comnd))(char **argd, char **infront)
{
	builtin_t funcs[] = {
		{ "exit", exit_shell },
		{ "env", env_shell },
		{ "setenv", setenv_shell },
		{ "unsetenv", unsetenv_shell },
		{ "cd", cd_shell },
		{ "alias", alias_shell },
		{ "help", help_shell },
		{ NULL, NULL }
	};
	int y;

	for (y = 0; funcs[y].name; y++)
	{
		if (_strcmp(funcs[y].name, comnd) == 0)
			break;
	}
	return (funcs[y].f);
}

/**
 * exit_shell - Causes normal process termination
 *                for the shellby shell.
 * @argd: An array of arguments containing the exit value.
 * @infront: A double pointer to the beginning of args.
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int exit_shell(char **argd, char **infront)
{
	int y, ren_of_int = 10;
	unsigned int num = 0, maxx = 1 << (sizeof(int) * 8 - 1);

	if (argd[0])
	{
		if (argd[0][0] == '+')
		{
			y = 1;
			ren_of_int++;
		}
		for (; argd[0][y]; y++)
		{
			if (y <= ren_of_int && argd[0][y] >= '0' && argd[0][y] <= '9')
				num = (num * 10) + (argd[0][y] - '0');
			else
				return (creates_error(--argd, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > maxx - 1)
		return (creates_error(--argb, 2));
	argb -= 1;
	frees_argd(argb, infront);
	frees_env();
	frees_alias_list(aliass);
	exit(num);
}

/**
 * cd_shell - Changes the current directory of the shellby process.
 * @argb: An array of arguments.
 * @infront: A double pointer to the beginning of args.
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int cd_shell(char **argb, char __attribute__((__unused__)) **infront)
{
	char **info_info, *newline = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat dir;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (argb[0])
	{
		if (*(argb[0]) == '-' || _strcmp(argb[0], "--") == 0)
		{
			if ((argb[0][1] == '-' && argb[0][2] == '\0') ||
					argb[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldp_wd);
				return (creates_error(argb, 2));
			}
		}
		else
		{
			if (stat(argb[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(argb[0]);
			else
			{
				free(old_pwd);
				return (creates_error(argb, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	info_dir = malloc(sizeof(char *) * 2);
	if (!info_dir)
		return (-1);

	info_dir[0] = "OLDPWD";
	info_dir[1] = oldpwd;
	if (setenv_shell(info_dir, info_dir) == -1)
		return (-1);

	info_dir[0] = "PWD";
	info_dir[1] = pwd;
	if (setenv_shell(info_dir, info_dir) == -1)
		return (-1);
	if (argb[0] && argb[0][0] == '-' && argb[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, newline, 1);
	}
	free(old_pwd);
	free(pwd);
	free(info_dir);
	return (0);
}

/**
 * help_shell - Displays information about shellby builtin commands.
 * @argb: An array of arguments.
 * @infront: A pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int help_shell(char **argb, char __attribute__((__unused__)) **infront)
{
	if (!argb[0])
		all_helps();
	else if (_strcmp(argb[0], "alias") == 0)
		alias_helps();
	else if (_strcmp(argb[0], "cd") == 0)
		cd_helps();
	else if (_strcmp(argb[0], "exit") == 0)
		exit_help();
	else if (_strcmp(argb[0], "env") == 0)
		_env();
	else if (_strcmp(argb[0], "setenv") == 0)
		_setenv();
	else if (_strcmp(argb[0], "unsetenv") == 0)
		_unsetenv();
	else if (_strcmp(argb[0], "help") == 0)
		help_helps();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
