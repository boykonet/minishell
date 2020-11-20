/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 13:44:05 by snaomi            #+#    #+#             */
/*   Updated: 2020/09/18 11:02:15 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_gnl
{
	int				fd;
	char			*reminder;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
/* int					get_line(char **line, char *buf, w_list *tmp); */
t_gnl				*ft_lstnew_gnl(int fd);

#endif
