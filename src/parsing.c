#include "../include/nemergent.h"

int	parsing(int argc, char **argv, t_n *n)
{
	int	fd;
	
	if (!(argc == 2 || argc == 3))
		return (close_n("Incorrect usage. Use \"-h\" or \"--help\" for usage information\n", n), 1);
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))
			return (close_n("Incorrect usage. Use \"-h\" or \"--help\" for usage information\n", n), 1);
		else
			return (printf("Usage: <./nemergent> <-f/--file> </path/to/cfg.txt>\n"), free_memory(n), 1); //--help
	}
	if (strcmp(argv[1], "-f") && strcmp(argv[1], "--file"))
		return (close_n("Incorrect usage. Use \"-h\" or \"--help\" for usage information\n", n), 1);
	if (strncmp(&argv[2][strlen(argv[2]) - 4], ".txt", 4))
		return (close_n("Incorrect cfg file extension, must be .txt\n", n), 1);
	fd = open(argv[2], O_RDONLY);
	if (fd < 0)
		return (close_n("Cannot open cfg file\n", n), 1);
	if (read_cfg(fd, n))
		return (1);
	if (parse_cfg_content(n))
		return (1);
	return (0);
}

int	read_cfg(int fd, t_n *n)
{
	char	*tmp = strdup("");
	char	*line;

	if (!tmp)
		return (close_n("Couldn't alloc tmp in read_cfg\n", n), 1);
	while (line = get_next_line(fd))
	{
		tmp = n_strjoin(tmp, line);
		if (!tmp)
			return (close_n("Couldn't alloc tmp in read_cfg\n", n), 1);
		free (line);
		n->cfg_lines++;
	}
	close (fd);
	if (n->cfg_lines != 2)
		return (free(tmp), close_n("Invalid cfg file1. Usage: \nnumbers_per_thread = <number> \nthread_num = <number>\n", n), 1);
	n->cfg_file = ft_split(tmp, '\n');
	free(tmp);
	if (parse_cfg_content(n));
	return (0);
}

int	parse_cfg_content(t_n *n)
{
	char *endptr;
	
	int	size1 = strlen("numbers_per_thread = ");
	int	size2 = strlen("thread_num = ");
	if (strncmp(n->cfg_file[0], "numbers_per_thread = ", size1))
		return (close_n("Invalid cfg file2. Usage: \nnumbers_per_thread = <number> \nthread_num = <number>\n", n), 1);
	if (strncmp(n->cfg_file[1], "thread_num = ", size2))
		return (close_n("Invalid cfg file3. Usage: \nnumbers_per_thread = <number> \nthread_num = <number>\n", n), 1);
	n->nmb_per_th = strtol(&n->cfg_file[0][size1], &endptr, 10);
	if (endptr == &n->cfg_file[0][size1] || *endptr != '\0' || n->nmb_per_th < 0)
		return (close_n("Invalid numbers_per_thread", n), 1);
	n->th_num = strtol(&n->cfg_file[1][size2], &endptr, 10);
	if (endptr == &n->cfg_file[1][size2] || *endptr != '\0' || n->th_num < 0)
		return (close_n("Invalid thread_num", n), 1);
	return (0);	 
}
