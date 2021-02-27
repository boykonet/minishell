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
#include "utils.h"

static void		newline(t_list **curr, int *flag)
{
	char		*str;

	while (curr && *curr && !ft_strncmp((*curr)->content, "-", 1))
	{
		str = (*curr)->content + 1;
		while (str && ft_strchr(str, 'n'))
			str++;
		if (!ft_strcmp(str, ""))
		{
			*flag = 1;
			(*curr) = (*curr)->next;
		}
		else
			break ;
	}
}

int				ft_echo(t_list *args)
{
	t_list		*curr;
	int			flag;

	flag = 0;
	curr = args;
	newline(&curr, &flag);
	while (curr)
	{
		ft_putstr_fd(curr->content, 1);
		if (curr->next)
			ft_putstr_fd(" ", 1);
		curr = curr->next;
	}
	if (!flag)
		ft_putendl_fd("", 1);
	return (0);
}
