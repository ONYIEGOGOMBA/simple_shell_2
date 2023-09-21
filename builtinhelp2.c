#include "shell.h"

/**
 * _env - Displays information on the shellby builtin command 'env'.
 */
void _env(void)
{
	char *mssg = "env: env\n\tPrints current environment.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * _setenv - Displays information on the shellby builtin command 'setenv'.
 */
void _setenv(void)
{
	char *mssg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * _unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void _unsetenv(void)
{
	char *mssg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "message to stderr.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}
