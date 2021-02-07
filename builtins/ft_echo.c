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

#include "builtins.h"
#include "other.h"

int		ft_echo(t_list *args, int fd)
{
	char	*str;
	int		flag;

	flag = 0;
	while (args && !ft_strncmp(args->content, "-", 1))
	{
		str = args->content + 1;
		if (str && !ft_strcmp(str, "n"))
		{
			flag = 1;
			args = args->next;
		}
		else
			break ;
	}
	while (args)
	{
		ft_putstr_fd(args->content, fd);
		if (args->next)
			ft_putstr_fd(" ", fd);
		args = args->next;
	}
	if (!flag)
		ft_putendl_fd("", fd);
	return (0);
}
