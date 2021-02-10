/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unexpected_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:35:29 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/10 23:35:29 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_unexpected_token(char **name_fd)
{
	char		**err;
	char		*tmp;
	int			i;

	i = 0;
	tmp = *name_fd;
	err = (char*[]) {">>", "<<", ";;", "||", "<", ">", "(", ")", ";", \
						"|", "", NULL};
	while (err[i])
	{
		if (**name_fd == *err[i] && \
		!ft_strncmp(err[i], *name_fd, ft_strlen(err[i])) && \
		!ft_isalpha(*(*name_fd + ft_strlen(err[i]))))
		{
			if (!ft_strncmp(*name_fd, "", ft_strlen(*name_fd)))
				*name_fd = ft_strdup("newline");
			else
				*name_fd = ft_strdup(err[i]);
			free(tmp);
			if (!*name_fd)
				exit(errno);
			return (0);
		}
		i++;
	}
	return (1);
}
