/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcharacter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:30:51 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/10 19:30:51 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				getcharacter(int fd, char **line)
{
	char		buff[2];
	char		*tmp;
	int			len;

	len = 0;
	ft_memset(buff, '\0', 2);
	(*line) = ft_strdup("");
	while ((len = read(fd, buff, 1)) >= 0)
	{
		tmp = (*line);
		if (buff[0] == '\n' || len == 0)
			break ;
		if (!((*line) = ft_strjoin((*line), buff)))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	len = len > 0 ? 1 : len;
	return (len);
}
