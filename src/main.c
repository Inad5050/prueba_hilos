#include "../include/nemergent.h"

int	main(int argc, char **argv)
{
	t_n	*n = calloc(1, sizeof(t_n));
	
	if (parsing(argc, argv, n))
		return (1);
	
	for (int i = 0; n->cfg_file[i]; i++)
		printf("cfg_file[%d] = %s\n", i, n->cfg_file[i]);
	printf("nmb_per_th = %ld\n", n->nmb_per_th);
	printf("th_num = %ld\n", n->th_num);








	free_memory(n);
	return (0);
}