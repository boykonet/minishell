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

char		*ft_echo(t_str *s_str, t_data *data, int fd)
{
	int		back_slash;
	int		i;

	back_slash = 0;
	i = 0;
	s_str->curr = s_str->args;
	if (!ft_strncmp(flags, "-n", 2))
		back_slash = 1;
	while (s_str->curr)
	{
		if (s_str->args_size - i == 0)
			write_str((s_str->curr)->content, fd, 1);
		else
			write_str((s_str->curr)->content, fd, 0);
		(s_str->curr) = (s_str->curr)->next;
		i++;
	}
	if (back_slash == 0)
		write(fd, "\n", 1);
}
