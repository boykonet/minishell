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

char		*ft_echo(t_params *params)
{
	t_list	*curr;
	int		back_slash;
	int		i;

	back_slash = 0;
	i = 0;
	curr = params->args;
	if (!ft_strncmp(params->flags, "n", 1))
		back_slash = 1;
	while (curr)
	{
		if (params->args_size - i == 0)
			write_str((params->curr)->content, fd, 1);
		else
			write_str((params->curr)->content, fd, 0);
		(params->curr) = (params->curr)->next;
		i++;
	}
	if (back_slash == 0)
		write(fd, "\n", 1);
}
