/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:03:10 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 21:03:10 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		write_str(char *str, int fd, int flag)
{
	write(1, str, ft_strlen(str));
	if (flag == 0)
		write(1, " ", 1);
}
