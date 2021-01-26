/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:50:10 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/29 16:50:10 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	dist_string_positive(t_data *data, int len_str)
{
	if (data->flag_neg == -1)
		data->prec = len_str;
	if (data->width > len_str && data->dot == 0)
		data->s_arr = data->width;
	else if (data->width <= len_str && data->dot == 0)
		data->s_arr = len_str;
	if (data->width < data->prec && data->dot == 1)
		if (data->prec < len_str)
		{
			data->s_arr = data->prec;
			len_str = data->prec;
		}
		else
			data->s_arr = data->width < len_str ? len_str : data->width;
	else if (data->width >= data->prec && data->dot == 1)
	{
		data->s_arr = data->width;
		if (data->width < len_str)
			len_str = data->prec;
		if (data->width >= len_str && data->prec < len_str)
			len_str = data->prec;
		if (data->width >= len_str && data->prec >= len_str)
			data->prec = len_str;
	}
	return (len_str);
}

int			dist_string(t_data *data, int len_str)
{
	if (data->flag_neg == -1 && data->flag_zero == 0)
	{
		data->s_arr = len_str;
		data->prec = len_str;
	}
	else
		len_str = dist_string_positive(data, len_str);
	return (len_str);
}
