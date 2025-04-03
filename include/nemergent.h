#ifndef NEMERGENT_H
#define NEMERGENT_H

# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"
# include "string.h"

typedef struct s_nemergent
{
	long int	nmb_per_th;
	long int	th_num;
	char		**cfg_file;
	int			cfg_lines;
} t_n;

//parsing
int			parsing(int argc, char **argv, t_n *n);
int			parse_cfg_file(char *file, int fd, t_n *n);
int			read_cfg(int fd, t_n *n);
int			parse_cfg_content(t_n *n);

//close
void		close_n(char *str, t_n *n);
void		free_memory(t_n *n);

//utils
char		*n_strjoin(char *s1, const char *s2);
static int	numstring(char const *s1, char c);
static int	numchar(char const *s2, char c, int i);
static char	**freee(char const **dst, int j);
static char	**affect(char const *s, char **dst, char c, int l);
char		**ft_split(char const *s, char c);
char		*ft_get_next_line(int fd);
char		*gnl_cut_line(char *line);
char		*gnl_excess(char *line);
char		*gnl_strjoin(char *line, const char *buffer);

#endif