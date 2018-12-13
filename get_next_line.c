/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:36:25 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/13 14:39:48 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"


#include <fcntl.h>
#include <stdio.h>

static char		*ft_str_increase(char *s1, size_t len1, size_t len2)
{
	char *conc;

	conc = ft_strnew(len1 + len2);
 	if (!conc)
	{
		if (s1)
			free(s1);
		return (NULL);
	}

 	if (!len1)
		return (conc);
 	ft_memmove(conc, s1, len1);
	if (s1)
		free(s1);
	return (conc);
}

static t_gnl	*ft_find_fd(const int fd, t_gnl **gnl)
{
	t_gnl	*temp;

	temp = *gnl;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	if (!(temp = malloc(sizeof(**gnl) * 1)))
		return (NULL);
	temp->fd = fd;
	temp->len = 0;
	temp->line = NULL;
	if (!gnl)
		temp->next = NULL;
	else
		temp->next = *gnl;
	(*gnl) = temp;
	return (temp);
}

static int		ft_search_newline(char *str, char **line, t_gnl *gnl, size_t j)
{
	size_t	i;

	gnl->len = 0;
	while (str && gnl->len < j)
		if (str[gnl->len++] == '\n')
		{
			*line = ft_strnew(gnl->len - 1);

			i = 0;
			while (i++ < gnl->len - 1)
				(*line)[i - 1] = str[i - 1];
			gnl->len = j - i;
			if (gnl->len && (gnl->line = ft_strnew(gnl->len)))
			{
				j = 0;
				while (j < gnl->len)
					gnl->line[j++] = str[i++];
			}
			return (1);
		}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*temp;
	char			*str;
	size_t			size;
	size_t			i;

	if (fd < 0 || !line || !(temp = ft_find_fd(fd, &gnl)))
		return (-1);
	if ((i = ft_search_newline(temp->line, line, temp, temp->len)))
		return (1);
	i = temp->len;
	str = ft_str_increase(temp->line, temp->len, BUFF_SIZE);
	while ((size = read(temp->fd, str + i, BUFF_SIZE)))
	{
		i += size;
		if (ft_search_newline(str, line, temp, i))
			return (1);
		str = ft_str_increase(str, i, BUFF_SIZE);
	}
	*line = ft_strnew(i);
	while (i--)
		(*line)[i] = str[i];
	return (0);
}


int					main(void)
{
	char	*str;
	int		fd;
	int		fd1;

	fd = open("test", O_RDONLY);
	fd1 = open("test1", O_RDONLY);
	int flag = 1;
	while (flag)
	{
		get_next_line(fd, &str);
		printf("%s\n", str);
		flag = get_next_line(fd1, &str);
		printf("%s\n", str);
	}
/* 	get_next_line(fd, &str);
		printf("line: %s\n", str);
	get_next_line(fd, &str);
		printf("line: %s\n", str);
	get_next_line(fd, &str);
		printf("line: %s\n", str);
	get_next_line(fd, &str);
		printf("line: %s\n", str); */
/* 	fd1 = open("test1", O_RDONLY);
	if (fd1 > -1)
	{
	get_next_line(fd1, &str);
		printf("line: %s\n", str);
	get_next_line(fd1, &str);
		printf("line: %s\n", str);
 	get_next_line(fd, &str);
		printf("line: %s\n", str);
	} */
	return (0);
}
