#include "../include/nemergent.h"

int	main(int argc, char **argv)
{
	t_n	*n = calloc(1, sizeof(t_n));
	
	if (parsing(argc, argv, n))
		return (1);
	if (init_struct(n))
		return (1);
		
/* 	for (int i = 0; n->cfg_file[i]; i++)
		printf("cfg_file[%d] = %s\n", i, n->cfg_file[i]);
	printf("nmb_per_th = %ld\n", n->nmb_per_th);
	printf("th_num = %ld\n", n->th_num); */

	if (threads(n))
		return (1);
	print_result(n);
	free_memory(n);
	return (0);
}

void	print_result(t_n *n)
{
	for (int i = 0; i < (n->nmb_per_th * n->th_num) && !n->s_even->numbers[i] && !n->s_even->numbers[i + 1]; i++)
		printf("even_list[%d] = %ld\n", i, n->s_even->numbers[i]);
	for (int i = 0; i < (n->nmb_per_th * n->th_num) && !n->s_odd->numbers[i] && !n->s_odd->numbers[i + 1]; i++)
		printf("odd_list[%d] = %ld\n", i, n->s_odd->numbers[i]);
}