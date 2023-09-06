#include "shell.h"
/**
 * my_exit - exits the shell
 * @info: struct containing potential arguments.
 * Return: given exit status
 */
int my_exit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _prratoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_error(info, "ilegal number: ");
			_pputs(info->argv[1]);
			_pputchar('\n');
			return (1);
		}
		info->err_num = _prratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * my_cd - changes current dir of the process
 * @info: struct containing potential arguments
 * Return: returns 0
 */
int my_cd(info_t *info)
{
	char *b, *bog, buffer[1024];
	int chng_dir;

	b = getcwd(buffer, 1024);
	if (!b)
		_puts("TOdo: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		bog = _getenv(info, "home=");
		if (bog)
			chng_dir = chng((bog = _getenv(info, "PWD=")) ? bog : "/");
		else
			chng_dir = chng(bog);
	}
	else if (_strcmp(info->argv[1], "_") == 0)
	{
		if (!_getenv(info, "oldpwd="))
		{
			_puts(b);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "oldpwd=")), _putchar('\n');
		chng_dir =
			chng((bog = _getenv(info, "oldpwd=")) ? bog : "/");
	}
	else
		chng_dir = chng(info->argv[1]);
	if (chng_dir == -1)
	{
		print_error(info, "can't cd to");
		_pputs(info->argv[1]), _pputchar('\n');
	}
	return (0);
}
/**
 * help_my - changes the current directory
 * @info: structure containing potential argument
 * Return: returns 0
 */
int help_my(info_t *info)
{
	char **bog_bog;

	bog_bog = info->argv;
	_puts("help call work \n");
	if (0)
		_puts(*bog_bog);
	return (0);
}
