/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:32:50 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:32:50 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	spec_with_flags(t_data *data, char ch, va_list ap,
			int (*f)(t_data*, va_list))
{
	if (*data->buff != ch)
	{
		if ((checker_printf(data, ap)) == -1)
			return (-1);
	}
	if ((f(data, ap)) == -1)
		return (-1);
	if (*data->buff == 'c')
	{
		if ((dist_char(data)) == -1)
			return (-1);
	}
	else
	{
		if ((dist_printf(data)) == -1)
			return (-1);
	}
	return (0);
}

int			printf_spec(t_data *data, va_list ap, char ch,
			int (*f)(t_data*, va_list))
{
	if (ch != *data->buff)
	{
		if ((spec_with_flags(data, ch, ap, f)) == -1)
			return (-1);
		return (0);
	}
	data->without_flags = 1;
	if ((f(data, ap)) == -1)
		return (-1);
	return (0);
}
