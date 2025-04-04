#include "../include/nem.h"

int	main(int argc, char **argv)
{
	t_n	*n = calloc(1, sizeof(t_n));
	
	if (parsing(argc, argv, n))
		return (1);
	if (init_struct(n))
		return (1);
	if (threads(n))
		return (1);
	sort_numbers(n);
	print_result(n);
	free_memory(n);
	return (0);
}

void	sort_numbers(t_n *n)
{
	int 		i, x;
	long int	tmp;

	for (i = 0; i + 1 < n->s_even->nmb_index; i++)
	{
		for (x = 0; x + 1 < n->s_even->nmb_index; x++)
		{
			if (n->s_even->numbers[x] > n->s_even->numbers[x + 1])
			{
				tmp = n->s_even->numbers[x];
				n->s_even->numbers[x] = n->s_even->numbers[x + 1];
				n->s_even->numbers[x + 1] = tmp;
			}
		}
	}
	for (i = 0; i + 1 < n->s_odd->nmb_index; i++)
	{
		for (x = 0; x + 1 < n->s_odd->nmb_index; x++)
		{
			if (n->s_odd->numbers[x] > n->s_odd->numbers[x + 1])
			{
				tmp = n->s_odd->numbers[x];
				n->s_odd->numbers[x] = n->s_odd->numbers[x + 1];
				n->s_odd->numbers[x + 1] = tmp;
			}
		}
	}
}

void	print_result(t_n *n)
{
	for (int i = 0; i < n->th_num; i++)
	{
		for (int x = 0; x < n->threads[i]->even_index; x++)
			printf("n->threads[%d]->even_numbers[%d] = %ld\n", i, x, n->threads[i]->even_numbers[x]);
			printf("\n");
		for (int x = 0; x < n->threads[i]->odd_index; x++)
			printf("n->threads[%d]->odd_numbers[%d] = %ld\n", i, x, n->threads[i]->odd_numbers[x]);
		printf("--------------\n");
	}
	for (int i = 0; i < (n->nmb_per_th * n->th_num) && n->s_even->numbers[i]; i++)
		printf("even_list[%d] = %ld\n", i, n->s_even->numbers[i]);
	printf("\n");
	for (int i = 0; i < (n->nmb_per_th * n->th_num) && n->s_odd->numbers[i]; i++)
		printf("odd_list[%d] = %ld\n", i, n->s_odd->numbers[i]);
	printf("--------------\n");
}
