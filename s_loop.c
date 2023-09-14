#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t l = 0;
	int builtin_ret = 0;

	while (l != -1 && builtin_ret != -2)
	{
		clearenv(info);
		if (interact(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		r = gets_put(info);
		if (l != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				finds_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
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
int builtin_find(info_t *info)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", my_histo},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _mycd},
		{"my_alias", my_alias},
		{NULL, NULL}
	};
	for (y = 0; builtintbl[y].typo; y++)
		if (_strcmp(info->argv[0], builtintbl[y].typo) == 0)
		{
			info->line_count++;
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
void cmd_find(info_t *info)
{
	char *path = NULL;
	int y, q;

	info->paths = info->argv[0];
	if (info->linecount_lagg == 1)
	{
		info->line_count++;
		info->linecount_lagg = 0;
	}
	for (y = 0, q = 0; info->arg[y]; y++)
		if (!is_dell(info->arg[y], " \t\n"))
			q++;
	if (!q)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->paths = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && finds_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_fork(info_t *info)
{
	pid_t child_pid
		child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->paths, info->argv, get_envir(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
