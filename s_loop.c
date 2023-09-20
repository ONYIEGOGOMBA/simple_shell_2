#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shh(info_t *info, char **av)
{
	ssize_t l = 0;
	int builtin_ret = 0;

	while (l != -1 && builtin_ret != -2)
	{
		clears_info(info);
		if (interact(info))
			_puts("$ ");
		_pputchar(BUF_FLUSH);
		l = gets_input(info);
		if (l != -1)
		{
			sets_info(info, av);
			builtin_ret = finds_builtin(info);
			if (builtin_ret == -1)
				finds_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		frees_info(info, 0);
	}
	write_histo(info);
	frees_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_numb == -1)
			exit(info->status);
		exit(info->err_numb);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int finds_builtin(info_t *info)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"envi", my_env},
		{"help", my_help},
		{"histo", my_histo},
		{"set_env", set_env},
		{"unset_env", unset_env},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};
	for (y = 0; builtintbl[y].typo; y++)
		if (_strcmp(info->argv[0], builtintbl[y].typo) == 0)
		{
			info->line_spell++;
			built_in_ret = builtintbl[y].funct(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PAT
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void finds_cmd(info_t *info)
{
	char *path = NULL;
	int y, q;

	info->paths = info->argv[0];
	if (info->linecount_lagg == 1)
	{
		info->line_spell++;
		info->linecount_lagg = 0;
	}
	for (y = 0, q = 0; info->arg[y]; y++)
		if (!is_dell(info->arg[y], " \t\n"))
			q++;
	if (!q)
		return;
	path = finds_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->paths = path;
		forks_cmd(info);
	}
	else
	{
		if ((interact(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && finds_cmd(info, info->argv[0]))
			forks_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prints_error(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forks_cmd(info_t *info)
{
	pid_t child_pid
		child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->paths, info->argv, get_envir(info)) == -1)
		{
			frees_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prints_error(info, "Permission denied\n");
		}
	}
}
