/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:36:25 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/13 17:26:13 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"


#include <fcntl.h>
#include <stdio.h>

static char		*ft_str_increase(char *s1, long long len1, long long len2)
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

static int		ft_search_newline(char *str, char **line, t_gnl *gnl, long long j)
{
	long long	i;

	gnl->len = 0;
	while (str && gnl->len < j)
		if (str[gnl->len++] == '\n')
		{
			if (!(*line = ft_strnew(gnl->len - 1)))
				return (0);
			i = 0;
			while (i++ < gnl->len - 1)
				(*line)[i - 1] = str[i - 1];
			gnl->len = j - i;
			if (gnl->len)
			{
 				if (!(gnl->line = ft_strnew(gnl->len)))
				 	return (0);
				j = 0;
				while (j < gnl->len)
					gnl->line[j++] = str[i++];
			}
			return (2);
		}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*temp;
	char			*str;
	long long int	size;
	int				er;

	if (fd < 0 || !line || !(temp = ft_find_fd(fd, &gnl)))
		return (-1);
	if ((er = ft_search_newline(temp->line, line, temp, temp->len)) == 2)
		return (1);
	str = ft_str_increase(temp->line, temp->len, BUFF_SIZE);
	while ((size = read(temp->fd, str + temp->len, BUFF_SIZE)) > 0 && str && er)
	{
		if ((er = ft_search_newline(str, line, temp, (temp->len += size))) == 2)
			return (1);
		str = ft_str_increase(str, temp->len, BUFF_SIZE);
	}
	if (temp->len && size > -1)
	{
		*line = ft_strnew(temp->len);
		while (temp->len--)
			(*line)[temp->len] = str[temp->len];
		return (1);
	}
	return (size <= -1 ? -1 : 0);
}

/* int	ft_memclr(char *str, char **line, t_gnl *temp, int size)
{

} */