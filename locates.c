#include "shell.h"
/**
 * gets_location - Locates a command in the PATH.
 * @comnd: The command to locate.
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *gets_location(char *comnd)
{
	char **paths, *tem;
	list_t *dirs, *hed;
	struct stat st;

	paths = _getenv("PATH");
	if (!paths || !(*paths))
		return (NULL);

	dirs = gets_path(*paths + 5);
	hed = dirs;

	while (dirs)
	{
		tem = malloc(_strlen(dirs->dir) + _strlen(comnd) + 2);
		if (!tem)
			return (NULL);

		_strcpy(tem, dirs->dir);
		_strcat(tem, "/");
		_strcat(tem, comnd);

		if (stat(tem, &st) == 0)
		{
			frees_list(hed);
			return (tem);
		}

		dirs = dirs->next;
		free(tem);
	}

	frees_list(hed);

	return (NULL);
}

/**
 * fills_path - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @paths: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fills_path(char *paths)
{
	int y, lengt = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (y = 0; paths[y]; y++)
	{
		if (paths[y] == ':')
		{
			if (paths[y + 1] == ':' || y == 0 || paths[y + 1] == '\0')
				lengt += _strlen(pwd) + 1;
			else
				lengt++;
		}
		else
			lengt++;
	}
	path_copy = malloc(sizeof(char) * (lengt + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (y = 0; paths[y]; y++)
	{
		if (paths[y] == ':')
		{
			if (y == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (paths[y + 1] == ':' || paths[y + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &paths[y], 1);
		}
	}
	return (path_copy);
}

/**
 * gets_path - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @paths: The colon-separated list of directories.
 * Return: A pointer to the initialized linked list.
 */
list_t *gets_path(char *paths)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fills_path(paths);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			frees_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
