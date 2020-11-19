/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:05:19 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/18 21:05:19 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_echo(char **arg, int fd)
{
	int		i;
	int		back_slash;

	i = 1;
	back_slash = 0;
	if (ft_strnstr(arg[i], "-n"))
		back_slash = 1;
	while (arg[i])
	{
		write(fd, arg[i], ft_strlen(arg[i]));
/* последний пробел не распечатывается!!!*/
		write(fd, " ", 1);
	}
	if (back_slash != 1)
		write(fd, "\n", 1);
}
