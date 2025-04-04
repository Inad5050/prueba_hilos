#ifndef NEMERGENT_H
#define NEMERGENT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>

typedef struct s_even
{
	long int		*numbers;
	int				nmb_index;
	pthread_mutex_t	even_mutex;
	int				mutex_flag;
} t_even;

typedef struct s_odd
{
	long int		*numbers;
	int				nmb_index;
	pthread_mutex_t	odd_mutex;
	int				mutex_flag;
} t_odd;

typedef struct s_thread
{
	unsigned int		thread_index;
	pthread_t			pthread;
	long int			*all_numbers;
	long int			*odd_numbers;
	int					odd_index;
	long int			*even_numbers;
	int					even_index;
	struct s_nem		*n;
} t_thread;

typedef struct s_nem
{
	long int	nmb_per_th;
	long int	th_num;
	char		**cfg_file;
	int			cfg_lines;
	t_even		*s_even;
	t_odd		*s_odd;
	t_thread	**threads;
} t_n;


//close
void		close_n(char *str, t_n *n);
void		free_memory(t_n *n);
void		free_thread(t_thread *t);

//init
int			init_struct(t_n *n);
int			init_thread(t_thread *t, t_n *n);

//main
void		print_result(t_n *n);
void		sort_numbers(t_n *n);

//parsing
int			parsing(int argc, char **argv, t_n *n);
int			read_cfg(int fd, t_n *n);
int			parse_cfg_content(t_n *n);

//threads
int			threads(t_n *n);
void		*f_thread(void *struct_ptr);
void		is_it_repeated(int i, t_thread *t);

//utils
char		*n_strjoin(char *s1, const char *s2);
static int	numstring(char const *s1, char c);
static int	numchar(char const *s2, char c, int i);
static char	**freee(char const **dst, int j);
static char	**affect(char const *s, char **dst, char c, int l);
char		**ft_split(char const *s, char c);
char		*ft_strdup(char *str);
char		*get_next_line(int	fd);

#endif