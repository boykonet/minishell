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

void		ft_echo(char **arg, int fd, int )
{
	int		i;
	int		back_slash;

	i = 1;
	back_slash = 0;
	if (ft_strnstr(arg[i], "-n"))
		back_slash = 1;
	while (arg[i])
	{
		if (i - 1 == )
		write_str(arg[i], fd, 0);
	}
	if (back_slash != 1)
		write(fd, "\n", 1);
}
