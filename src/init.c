#include "../include/nemergent.h"

int	init_struct(t_n *n)
{
	n->s_even = calloc(1, sizeof(t_even));
	if (!n->s_even)
		return (close_n("Couldn't alloc s_even in init_struct\n", n), 1);
	n->s_odd = calloc(1, sizeof(t_odd));
	if (!n->s_odd)
		return (close_n("Couldn't alloc s_odd in init_struct\n", n), 1);
	n->s_even->numbers = calloc(n->nmb_per_th * n->th_num, sizeof(long int));
	if (!n->s_even->numbers)
		return (close_n("Couldn't alloc s_even->numbers in init_struct\n", n), 1);
	n->s_odd->numbers = calloc(n->nmb_per_th  * n->th_num, sizeof(long int));
	if (!n->s_odd->numbers)
			return (close_n("Couldn't alloc s_odd->numbers in init_struct\n", n), 1);
	if (pthread_mutex_init(&n->s_even->even_mutex, NULL))
			return (close_n("Couldn't pthread_mutex_init even_mutex in init_struct\n", n), 1);
	n->s_even->mutex_flag = 1;
	if (pthread_mutex_init(&n->s_odd->odd_mutex, NULL))
			return (close_n("Couldn't pthread_mutex_init odd_mutex in init_struct\n", n), 1);
	n->s_odd->mutex_flag = 1;
	n->threads = calloc(n->th_num, sizeof(t_thread*));
	if (!n->threads)
		return (close_n("Couldn't alloc n->threads in init_struct\n", n), 1);
	for (int i = 0; i < n->th_num; i++)
	{
		n->threads[i] = calloc(n->th_num, sizeof(t_thread*));
		if (!n->threads[i])
			return (close_n("Couldn't alloc n->threads in init_struct\n", n), 1);
		if (init_thread(n->threads[i], n))
			return (1);
	}
	return (0);
}

int	init_thread(t_thread *t, t_n *n)
{
	t->n = n;
	t->all_numbers = calloc(n->nmb_per_th, sizeof(long int));
	if (!t->all_numbers)
		return (close_n("Couldn't alloc t->all_numbers in init_thread\n", n), 1);
	t->even_numbers = calloc(n->nmb_per_th, sizeof(long int));
	if (!t->even_numbers)
		return (close_n("Couldn't alloc t->even_numbers in init_thread\n", n), 1);
	t->odd_numbers = calloc(n->nmb_per_th, sizeof(long int));
	if (!t->odd_numbers)
		return (close_n("Couldn't alloc t->odd_numbers in init_thread\n", n), 1);
}
