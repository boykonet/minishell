/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:33:08 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:33:08 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int			get_data_u(t_data *data, va_list ap)
{
	unsigned int	var;

	var = (unsigned int)va_arg(ap, int);
	if ((data->var = ft_itoa_base(var, 10)) == NULL)
		return (-1);
	return (0);
}

int					printf_u(t_data *data, va_list ap, char *s)
{
	if ((printf_spec(data, ap, *s, &get_data_u)) == -1)
		return (-1);
	return (0);
}
