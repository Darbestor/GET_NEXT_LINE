/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:32:29 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/14 19:39:42 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 150

typedef struct	s_gnl
{
	int					fd;
	char				*line;
	long long int		len;
	struct s_gnl		*next;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
