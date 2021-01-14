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

int			add_fd(char *file, char *redir)
{
	int		fd;

	fd = -2;
	if (!ft_strncmp(redir, "<", ft_strlen(redir)))
		fd = open(file, O_RDONLY);
	else if (!ft_strncmp(redir, ">", ft_strlen(redir))/* || \
			!ft_strncmp(redir, "1>", ft_strlen(redir)) || \
			!ft_strncmp(redir, "2>", ft_strlen(redir))*/)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!ft_strncmp(redir, ">>", ft_strlen(redir))/* || \
			!ft_strncmp(redir, "1>>", ft_strlen(redir)) || \
			!ft_strncmp(redir, "2>>", ft_strlen(redir))*/)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}
