/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 09:08:32 by snaomi            #+#    #+#             */
/*   Updated: 2020/09/18 11:08:25 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

w_list		*ft_lstnew_gnl(int fd)
{
	w_list *tmp;

	tmp = (w_list*)malloc(sizeof(w_list));
	if (tmp)
	{
		tmp->fd = fd;
		tmp->reminder = NULL;
		tmp->next = NULL;
		return (tmp);
	}
	else
		return (0);
}
