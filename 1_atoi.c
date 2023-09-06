#include "shell.h"
/**
 * interact - it returns true if the shell interacts
 * @info: struct address
 * Return: the mode
 */
int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readpd <= 2);
}
/**
 * is_dell - checks the character if it is delimeter
 * @o: the cahracter
 * @deli: the delimeter string
 * Return: true 1 false 0
 */
int is_dell(char o, char *deli)
{
	while (*deli)
		if (*deli++ == o)
			return (1);
	return (0);
}
/**
 * is_alpha - aplphabet check
 * @o: the character
 * Return: alphabet 1, 0 otherwise
 */
int is_alpha(int o)
{
	if ((o >= 'a' && o <= 'z') || (o >= 'A' && o <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * a_toil - converts a string to an integer
 * @b: the string to be converted
 * Return: 0 if string converted no otherwise
 */
int a_toil(char *b)
{
	int g, signal = 1, lagg = 0, output;
	unsigned int ress = 0;

	for (g = 0; b[g] != '\0' && lagg != 2; g++)
	{
		if (b[g] == '-')
			signal *= -1;
		if (b[g] >= '0' && b[g] <= '9')
		{
			lagg = 1;
			ress *= 10;
			ress += (b[g] - '0');
		}
		else if (lagg == 1)
			lagg = 2;
	}
	if (signal == -1)
		output = -ress;
	else
		output = ress;
	return (output);
}
