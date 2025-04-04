#include "../include/nem.h"

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
	if (n->s_even)
	{
		if (n->s_even->numbers)
			free(n->s_even->numbers);
		if (n->s_even->mutex_flag)
			pthread_mutex_destroy(&n->s_even->even_mutex);
		free(n->s_even);
	}
	if (n->s_odd)
	{
		if (n->s_odd->numbers)
			free(n->s_odd->numbers);
		if (n->s_odd->mutex_flag)
			pthread_mutex_destroy(&n->s_odd->odd_mutex);
		free(n->s_odd);
	}
	if (n->threads)
	{
		for (int i = 0; i < n->th_num; i++)
			free_thread(n->threads[i]);
		free(n->threads);
	}
	free(n);
	exit(1);
}

void	free_thread(t_thread *t)
{
	if (t->all_numbers)
		free(t->all_numbers);
	if (t->even_numbers)
		free(t->even_numbers);
	if (t->odd_numbers)
		free(t->odd_numbers);
	free(t);
}