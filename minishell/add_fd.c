/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.r       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:45:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/17 22:45:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			add_fd(char *in, char *redir)
{
	int		fd;

	fd = 1;
	if (!ft_strncmp(redir, ">>", 2))
	{
		if ((fd = open(in, O_CREAT | O_RDWR | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (fd);
	}
	else if (!ft_strncmp(redir, ">", 1))
	{
		if ((fd = open(in, O_CREAT | O_RDWR | O_TRUNC, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (fd);
	}
	else if (!ft_strncmp(redir, "<", 1))
	{
		; /* ya ne znau cho etot redirect delaet */
	}
	return (fd);
}
