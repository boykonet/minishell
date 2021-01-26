/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:31:55 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:31:55 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int		get_data_p(t_data *data, va_list ap)
{
	char			*p;
	long int		num;

	num = (long int)va_arg(ap, size_t);
	if ((p = ft_itoa_base(num, 16)) == NULL)
		return (-1);
	if ((data->var = ft_strjoin("0x", p)) == NULL)
	{
		free(p);
		return (-1);
	}
	free(p);
	return (0);
}

int				printf_p(t_data *data, va_list ap, char *s)
{
	if ((printf_spec(data, ap, *s, &get_data_p)) == -1)
		return (-1);
	return (0);
}
