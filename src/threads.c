#include "../include/nem.h"

int	threads(t_n *n)
{
	for (int i = 0; i < n->th_num; i++)
	{
		if (pthread_create(&n->threads[i]->pthread, NULL, &f_thread, n->threads[i]))
			return (close_n("Failed to create thread", n), 1);
	}
	for (int i = 0; i < n->th_num; i++)
		pthread_join(n->threads[i]->pthread, NULL);
	return (0);
}

void	*f_thread(void *struct_ptr)
{	
	t_thread		*t = (t_thread*)struct_ptr;
	unsigned int 	seed = time(NULL) + t->thread_index;

	for (int i = 0; i < t->n->nmb_per_th; i++)
	{
		t->all_numbers[i] = rand_r(&seed); //rand is not prepared to be used on a multithread enviroment, instead we will use rand_r()
		if (!t->all_numbers[i])
			t->all_numbers[i] += 1;
		is_it_repeated(i, t);
	}
	for (int i = 0; i < t->n->nmb_per_th; i++) //we will separate odd an even numbers in order to lock the mutexes as little as possible
	{
		if (t->all_numbers[i] % 2 == 0)
			t->even_numbers[t->even_index++] = t->all_numbers[i];
		else
			t->odd_numbers[t->odd_index++] = t->all_numbers[i];
	}

	pthread_mutex_lock(&t->n->s_even->even_mutex);
	for (int i = 0; i < t->even_index; i++)
	{
		if (t->n->s_even->nmb_index > (t->n->nmb_per_th * t->n->th_num))
			return (pthread_mutex_unlock(&t->n->s_even->even_mutex), \
			perror("Invalid index writing on s_even->numbers"), NULL);
		t->n->s_even->numbers[t->n->s_even->nmb_index++] = t->even_numbers[i];
	}
	pthread_mutex_unlock(&t->n->s_even->even_mutex);

	pthread_mutex_lock(&t->n->s_odd->odd_mutex);
	for (int i = 0; i < t->odd_index; i++)
	{
		if (t->n->s_odd->nmb_index > (t->n->nmb_per_th * t->n->th_num))
			return (pthread_mutex_unlock(&t->n->s_even->even_mutex), \
			perror("Invalid index writing on s_odd->numbers"), NULL);
		t->n->s_odd->numbers[t->n->s_odd->nmb_index++] = t->odd_numbers[i];
	}
	pthread_mutex_unlock(&t->n->s_odd->odd_mutex);

	return (NULL);
}

void	is_it_repeated(int i, t_thread *t)
{
	int x = 0;
	while (x < i)
	{
		if (t->all_numbers[i] == t->all_numbers[x])
		{
			t->all_numbers[i] += 1;
			is_it_repeated(i, t);
		}
		x++;
	}
	return;
}
