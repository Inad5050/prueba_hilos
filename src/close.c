#include "../include/nemergent.h"

void	close_n(char *str, t_n *n)
{
	perror(str);
	free_memory(n);
}

void	free_memory(t_n *n)
{
	if (n->cfg_file)
	{
		for (int i = 0; n->cfg_file[i]; i++)
			free(n->cfg_file[i]);
		free(n->cfg_file);
	}
	free(n);
	exit(1);
}