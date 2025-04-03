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

//get_next_line

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

char	*ft_strdup(char *str)
{
	int	i = 0;
	
	while (str[i])
		i++;
	char	*dup = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int	fd)
{
	static char	buffer[42000];
	static int buffer_index;
	static int buffer_readed;
	char	line[70000];
	int	i = 0;

	if (fd < 0 || 42 <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_index >= buffer_readed)
		{
			buffer_readed = read(fd, buffer, 42);
			buffer_index = 0;
			if (buffer_readed <= 0)
				break ;
		}
		line[i++] = buffer[buffer_index++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
