#include "shell.h"
/**
 * shell_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @argb: An array of arguments.
 * @infront: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_alias(char **argb, char __attribute__((__unused__)) **infront)
{
	alias_t *tem = aliass;
	int y, rett = 0;
	char *value;

	if (!argb[0])
	{
		while (tem)
		{
			prints_alias(tem);
			tem = tem->next;
		}
		return (rett);
	}
	for (y = 0; argb[y]; y++)
	{
		tem = aliass;
		value = _strchr(argb[y], '=');
		if (!value)
		{
			while (tem)
			{
				if (_strcmp(argb[y], tem->name) == 0)
				{
					prints_alias(tem);
					break;
				}
				tem = tem->next;
			}
			if (!tem)
				rett = creates_error(argb + y, 1);
		}
		else
			sets_alias(argb[y], value);
	}
	return (rett);
}

/**
 * sets_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @varname: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void sets_alias(char *varname, char *value)
{
	alias_t *tem = aliass;
	int ren, k, q;
	char *newvalue;

	*value = '\0';
	value++;
	ren = _strlen(value) - _strspn(value, "'\"");
	newvalue = malloc(sizeof(char) * (ren + 1));
	if (!newvalue)
		return;
	for (k = 0, q = 0; value[k]; k++)
	{
		if (value[k] != '\'' && value[k] != '"')
			newvalue[q++] = value[k];
	}
	newvalue[q] = '\0';
	while (tem)
	{
		if (_strcmp(varname, tem->name) == 0)
		{
			free(tem->value);
			tem->value = newvalue;
			break;
		}
		tem = tem->next;
	}
	if (!tem)
		add_alias_end(&aliass, varname, newvalue);
}

/**
 * prints_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void prints_alias(alias_t *alias)
{
	char *string_alias;
	int ren = _strlen(alias->name) + _strlen(alias->value) + 4;

	string_alias = malloc(sizeof(char) * (ren + 1));
	if (!string_alias)
		return;
	_strcpy(string_alias, alias->name);
	_strcat(string_alias, "='");
	_strcat(string_alias, alias->value);
	_strcat(string_alias, "'\n");

	write(STDOUT_FILENO, string_alias, ren);
	free(string_alias);
}
/**
 * replaces_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @argb: 2D pointer to the arguments.
 * Return: 2D pointer to the arguments.
 */
char **replaces_aliases(char **argb)
{
	alias_t *tem;
	int y;
	char *newvalue;

	if (_strcmp(argb[0], "alias") == 0)
		return (argb);
	for (y = 0; argb[y]; y++)
	{
		tem = aliass;
		while (tem)
		{
			if (_strcmp(argb[y], tem->name) == 0)
			{
				newvalue = malloc(sizeof(char) * (_strlen(tem->value) + 1));
				if (!newvalue)
				{
					frees_argb(argb, argb);
					return (NULL);
				}
				_strcpy(newvalue, tem->value);
				free(argb[y]);
				argb[y] = newvalue;
				y--;
				break;
			}
			tem = tem->next;
		}
	}

	return (argb);
}
