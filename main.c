#include "shell.h"
/**
 * sigin_handler - Prints a new prompt upon a signal.
 * @sign: The signal.
 */
void sign_handler(int sign)
{
	char *new_promp = "\n$ ";

	(void)sign;
	signal(SIGINT, sign_handler);
	write(STDIN_FILENO, new_promp, 3);
}

/**
 * executes - Executes a command in a child process.
 * @argb: An array of arguments.
 * @infront: A double pointer to the beginning of args.
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int executes(char **argb, char **infront)
{
	pid_t child_pid;
	int status, flag = 0, rett = 0;
	char *comnd = argb[0];

	if (comnd[0] != '/' && comnd[0] != '.')
	{
		flag = 1;
		comnd = gets_location(comnd);
	}

	if (!comnd || (access(comnd, F_OK) == -1))
	{
		if (errno == EACCES)
			rett = (creates_error(argb, 126));
		else
			rett = (creates_error(argb, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(comnd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(comnd, argb, environ);
			if (errno == EACCES)
				rett = (creates_error(argb, 126));
			frees_env();
			frees_argb(argb, infront);
			frees_alias_list(aliass);
			_exit(rett);
		}
		else
		{
			wait(&status);
			rett = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(comnd);
	return (rett);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int rett = 0, retn;
	int *exec_ret = &retn;
	char *promp = "$ ", *newline = "\n";

	name = argv[0];
	hist = 1;
	aliass = NULL;
	signal(SIGINT, sign_handler);

	*exec_ret = 0;
	environ = _copiesenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		rett = proc_files_commands(argv[1], exec_ret);
		frees_env();
		frees_alias_list(aliases);
		return (*exec_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (rett != END_OF_FILE && rett != EXIT)
			rett = handles_argb(exec_ret);
		frees_env();
		frees_alias_list(aliases);
		return (*exec_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, promp, 2);
		rett = handles_argb(exec_ret);
		if (rett == END_OF_FILE || rett == EXIT)
		{
			if (rett == END_OF_FILE)
				write(STDOUT_FILENO, newline, 1);
			frees_env();
			frees_alias_list(aliases);
			exit(*exec_ret);
		}
	}

	frees_env();
	frees_alias_list(aliases);
	return (*exec_ret);
}
