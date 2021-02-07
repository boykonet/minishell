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

#include "other.h"

static int		eof_char(char **line, int len)
{
	if (len == 0)
	{
		write(1, "  \b\b", ft_strlen("  \b\b"));
		if (!ft_strlen(*line))
		{
			ft_putendl_fd("exit", 1);
			return (0);
		}
		return (1);
	}
	return (2);
}

int				getcharacter(int fd, char **line)
{
	char		buff[2];
	char		*tmp;
	int			len;
	int			sig;

	ft_memset(buff, '\0', 2);
	if (!((*line) = ft_strdup("")))
		exit(errno);
	while ((len = read(fd, buff, 1)) >= 0)
	{
		tmp = (*line);
		if (!(sig = eof_char(line, len)))
			return (0);
		else if (sig == 1)
			continue ;
		if (buff[0] == '\n')
			break ;
		(*line) = ft_strjoin((*line), buff);
		free(tmp);
		if (!(*line))
			exit(errno);
	}
	return (1);
}
