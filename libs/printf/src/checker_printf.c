/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:35:03 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:35:03 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	checker_flags(t_data *data)
{
	if (*data->buff == '-')
		data->sign = 1;
	else if (*data->buff == '0' && data->sign == 0)
		data->sign = 2;
	if (data->sign != 0)
		data->buff++;
}

static void	checker_width(t_data *data, va_list ap)
{
	if (*data->buff == '*' && data->dot == 0)
	{
		data->width = va_arg(ap, int);
		data->buff++;
	}
	else if ((*data->buff >= '0' && *data->buff <= '9') && data->dot == 0)
	{
		data->width = ft_atoi(data->buff);
		while (*data->buff >= '0' && *data->buff <= '9')
			data->buff++;
	}
}

static void	checker_precision(t_data *data, va_list ap)
{
	if (*data->buff == '.')
	{
		data->dot = 1;
		data->buff++;
	}
	if (*data->buff == '*')
	{
		data->prec = va_arg(ap, int);
		data->buff++;
	}
	else if (*data->buff >= '0' && *data->buff <= '9')
	{
		data->prec = ft_atoi(data->buff);
		while (*data->buff >= '0' && *data->buff <= '9')
			data->buff++;
	}
}

int			checker_printf(t_data *data, va_list ap)
{
	checker_flags(data);
	checker_width(data, ap);
	checker_precision(data, ap);
	return (0);
}
