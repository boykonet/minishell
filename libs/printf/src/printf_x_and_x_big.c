/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x_and_x_big.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:33:28 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:33:28 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int			get_data_x(t_data *data, va_list ap)
{
	unsigned int	x;

	x = (unsigned int)va_arg(ap, int);
	if ((data->var = ft_itoa_base(x, 16)) == NULL)
		return (-1);
	return (0);
}

static int			get_data_x_big(t_data *data, va_list ap)
{
	unsigned int	xx;
	int				i;

	i = 0;
	xx = (unsigned int)va_arg(ap, int);
	if ((data->var = ft_itoa_base(xx, 16)) == NULL)
		return (-1);
	while (data->var[i])
	{
		if (data->var[i] >= 'a' && data->var[i] <= 'x')
			data->var[i] = data->var[i] - 32;
		i++;
	}
	return (0);
}

int					printf_x_and_x_big(t_data *data, va_list ap, char *s)
{
	if (*s == 'x')
		if ((printf_spec(data, ap, *s, &get_data_x)) == -1)
			return (-1);
	if (*s == 'X')
		if ((printf_spec(data, ap, *s, &get_data_x_big)) == -1)
			return (-1);
	return (0);
}
