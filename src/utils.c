#include "../include/nemergent.h"

char	*n_strjoin(char *s1, const char *s2)
{
	int		i = 0;
	int		len_s1 = strlen(s1);
	int		len_s2 = strlen(s2);
	char	*result = calloc(len_s1 + len_s2 + 1, sizeof(char));

	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[len_s1 + i] = s2[i];
		i++;
	}
	result[len_s1 + i] = '\0';
	free(s1);
	return (result);
}

//split

static int	numstring(char const *s1, char c)
{
	int	comp;
	int	cles;

	comp = 0;
	cles = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		if (*s1 == c)
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			comp++;
		}
		s1++;
	}
	return (comp);
}

static int	numchar(char const *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char	**freee(char const **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

static char	**affect(char const *s, char **dst, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)calloc(numchar(s, c, i) + 1, sizeof(char));
		if (dst[j] == NULL)
			return (freee((char const **)dst, j));
		while (s[i] != '\0' && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		l;

	if (s == NULL)
		return (NULL);
	l = numstring(s, c);
	dst = (char **)calloc((l + 1), sizeof(char *));
	if (dst == NULL)
		return (NULL);
	return (affect(s, dst, c, l));
}

//get_next_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_get_next_line(int fd)
{
	static char	*line;
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!strchr(line, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		line = gnl_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	return_line = gnl_cut_line(line);
	line = gnl_excess(line);
	return (return_line);
}

char	*gnl_cut_line(char *line)
{
	char	*return_line;
	int		i;
	int		j;

	i = 0;
	if (!line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	return_line = calloc(i + 2, sizeof(char));
	if (!return_line)
		return (NULL);
	j = -1;
	while (++j <= i)
		return_line[j] = line[j];
	if (line[i] == '\n')
		return_line[++i] = '\0';
	return (return_line);
}

char	*gnl_excess(char *line)
{
	char	*excess;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (!line[i])
		return (free (line), NULL);
	excess = calloc(strlen(line) - i + 1, sizeof(char));
	if (!excess)
		return (NULL);
	while (line[i])
		excess[j++] = line[++i];
	excess[j] = '\0';
	free(line);
	return (excess);
}

char	*gnl_strjoin(char *line, const char *buffer)
{
	int		i;
	int		j;
	char	*str;

	if (!line)
	{
		line = (char *)calloc(1, sizeof(char));
		line[0] = '\0';
	}
	if (!line || !buffer)
		return (NULL);
	str = calloc((strlen(line) + strlen(buffer) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (line[++i])
		str[i] = line[i];
	while (buffer[j])
		str[i++] = buffer[j++];
	str[strlen(line) + strlen(buffer)] = '\0';
	free (line);
	return (str);
}
