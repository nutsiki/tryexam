#include "train_gnl.h"$
$
int		ft_strlen(char *str)$
{$
	int i = 0;$
	if (!*str)$
		return (0);$
	while (*str++)$
		i++;$
	return (i);$
}$
$
void 	*ft_strdup(char *str)$
{$
	char *new_str;$
	int i = 0;$
$
	if (!str)$
		return (NULL);$
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));$
	while (*str)$
		new_str[i++] = *str++;$
	new_str[i] = '\0';$
	return (new_str);$
}$
$
$
char 	*ft_strjoin(char *str1, char *str2)$
{$
	char *str;$
	int i = 0;$
$
	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));$
	while (str1 && *str1)$
		str[i++] = *str1++;$
	while (str2 && *str2)$
		str[i++] = *str2++;$
	str[i] = '\0';$
	return (str);$
}$
$
char	*ft_strchr(char *str, int c)$
{$
	if (!str)$
		return (NULL);$
	while (*str)$
	{$
		if (*str == c)$
			return (str);$
		str++;$
	}$
	if (c == '\0')$
		return (str);$
	return (0);$
}$
$
char *make_line(char *str)$
{$
	char *line;$
	int i = 0;$
$
	line = malloc(sizeof(char)*(ft_strlen(str) + 1));$
	while (*str != '\n')$
	{$
		line[i++] = *str++;$
	}$
	line[i] = '\0';$
	return (line);$
}$
$
int ft_chop(char **stat, char **line)$
{$
	char *tmp;$
	if (*stat && ft_strchr(*stat, '\n') > 0)$
	{$
		*line = make_line(*stat);$
		tmp = ft_strchr(*stat, '\n') + 1;$
		tmp = ft_strdup(tmp);$
		free(*stat);$
		*stat = tmp;$
		return (1);$
	}$
	else if (*stat != 0)$
		*line = ft_strdup(*stat);$
	else$
		*line = ft_strdup("");$
	return (0);$
$
}$
$
int get_next_line(char **line)$
{$
	char *buffer, *tmp;$
	static char *stat;$
	int size;$
$
	if ((!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)))) || !line || BUFFER_SIZE < 1 || read(0,buffer, 0) < 0)$
		return (-1);$
	while ((size = read(0, buffer, BUFFER_SIZE)) > 0)$
	{$
		buffer[size] = '\0';$
		if (!stat)$
			stat = ft_strdup("");$
		tmp = ft_strjoin(stat, buffer);$
		free(stat);$
		stat = tmp;$
		if (ft_strchr(stat, '\n'))$
			break;$
	}$
	free(buffer);$
	return(ft_chop(&stat, line));$
}$
