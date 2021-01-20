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

int			ft_echo(t_list *args)
{
	int 	flag;

	flag = 0;
	while (!ft_strncmp(args->content, "-n", ft_strlen(args->content)))
	{
		flag = 1;
		args = args->next;
	}
	while (args)
	{
		write(1, args->content, ft_strlen(args->content));
		if (args->next)
			write(1, " ", 1);
		args = args->next;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
