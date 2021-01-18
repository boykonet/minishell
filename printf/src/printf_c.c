/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:31:18 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:31:18 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int			get_data_c(t_data *data, va_list ap)
{
	data->c = (char)va_arg(ap, int);
	return (0);
}

int					printf_c(t_data *data, va_list ap, char *s)
{
	if ((printf_spec(data, ap, *s, &get_data_c)) == -1)
		return (-1);
	return (0);
}
