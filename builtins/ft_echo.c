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

int			ft_echo(t_list *args, int fd)
{
	int 	flag;

	flag = 0;
	while (args && !ft_strncmp(args->content, "-n", 2))
	{
		flag = 1;
		args = args->next;
	}
	while (args)
	{
		write(fd, args->content, ft_strlen(args->content));
		if (args->next)
			write(fd, " ", 1);
		args = args->next;
	}
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
