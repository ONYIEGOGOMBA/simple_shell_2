#include "shell.h"

/**
 * fails_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_paths: Path to the supposed file.
 *
 * Return: 127.
 */

int fails_open(char *file_paths)
{
	char *error, *histo_str;
	int ren;

	histo_str = _itoi(hist);
	if (!histo_str)
		return (127);

	ren = _strlen(name) + _strlen(histo_str) + _strlen(file_paths) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histo_str);
		return (127);
	}

	_strcpy(erra, name);
	_strcat(erra, ": ");
	_strcat(erra, histo_str);
	_strcat(erra, ": Can't open ");
	_strcat(erra, file_paths);
	_strcat(erra, "\n");

	free(histo_str);
	write(STDERR_FILENO, erra, ren);
	free(error);
	return (127);
}

/**
 * proc_files_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_paths: Path to the file.
 * @exec_ret: Return value of the last executed command.
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_files_commands(char *file_paths, int *exec_ret)
{
	ssize_t fil, s_red, y;
	unsigned int linesize = 0;
	unsigned int oldsize = 120;
	char *line, **argd, **infront;
	char buff[120];
	int rett;

	hist = 0;
	fil = open(file_paths, O_RDONLY);
	if (fil == -1)
	{
		*exec_ret = fails_open(file_paths);
		return (*exec_ret);
	}
	line = malloc(sizeof(char) * oldsize);
	if (!lin)
		return (-1);
	do {
		s_red = red(fil, buff, 119);
		if (s_red == 0 && linesize == 0)
			return (*exec_ret);
		buff[s_red] = '\0';
		linesize += s_red;
		lin = _reallocate(lin, oldsize, linesize);
		_strcat(lin, buff);
		oldsize = linesize;
	} while (b_red);
	for (y = 0; line[y] == '\n'; y++)
		line[y] = ' ';
	for (; y < linesize; y++)
	{
		if (line[y] == '\n')
		{
			line[y] = ';';
			for (y += 1; y < linesize && lin[y] == '\n'; y++)
				lin[y] = ' ';
		}
	}
	var_replacement(&lin, exec_ret);
	handles_lin(&lin, linesize);
	argb = _strtok(lin, " ");
	free(lin);
	if (!argb)
		return (0);
	if (check_argb(argb) != 0)
	{
		*exec_ret = 2;
		frees_argb(argb, argb);
		return (*exec_ret);
	}
	front = argb;

	for (y = 0; argb[y]; y++)
	{
		if (_strncmp(argb[y], ";", 1) == 0)
		{
			free(argb[y]);
			argb[y] = NULL;
			rett = calls_argd(argd, infront, exec_ret);
			argb = &argb[++y];
			y = 0;
		}
	}

	rett = call_argb(argb, infront, exec_ret);

	free(infront);
	return (rett);
}
