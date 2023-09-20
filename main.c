#include "shell.h"
/**
 * main - entry point
 * @pc: arg count
 * @va: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int pc, char **va)
{
	info_t info[] = { INFO_INIT };
	int pd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=l" (pd)
			: "l" (pd));
	if (pc == 2)
	{
		pd = open(va[1], O_RDONLY);
		if (pd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_pputs(va[0]);
				_pputs(": 0: Cant open ");
				_pputs(va[1]);
				_pputchar('\n');
				_pputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readpd = pd;
	}
	pops_env_list(info);
	read_histo(info);
	hss(info, va);
	return (EXIT_SUCCESS);
}
