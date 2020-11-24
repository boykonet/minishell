/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:14:51 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/23 18:14:51 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			init_fd(char *name_fd, char *redir)
{
	int		fd;

	fd = 1;
	if (!ft_strncmp(redir, ">>", 2))
	{
		if ((fd = open(name_fd, O_CREAT | O_RDWR | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (fd);
	}
	else if (!ft_strncmp(redir, ">", 1))
	{
		if ((fd = open(name_fd, O_CREAT | O_RDWR | O_TRUNC, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (fd);
	}
	else if (!ft_strncmp(redir, "<", 1))
	{
		; /* ya ne znau cho etot redirect delaet */
	}
	return (fd);
}
