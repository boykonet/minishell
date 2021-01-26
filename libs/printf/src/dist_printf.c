/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:35:36 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:35:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	dist_percent(t_data *data, int len_str, int diff_num)
{
	if (diff_num > 0)
	{
		data->s_arr = data->width;
		data->prec = data->sign == 2 ? data->s_arr : len_str;
	}
	else
	{
		data->prec = len_str;
		if (len_str > data->width && data->dot == 0)
			data->s_arr = len_str;
		else if (len_str <= data->width && data->dot == 0)
			data->s_arr = data->width;
		if (len_str > data->width && data->dot == 1)
			data->s_arr = len_str;
		else if (len_str <= data->width && data->dot == 1)
			data->s_arr = data->width;
		if (data->sign == 2)
			data->prec = data->s_arr;
	}
	return (len_str);
}

static void	neg_width_prec(t_data *data)
{
	if (data->width < 0)
	{
		data->sign = 1;
		data->width *= -1;
	}
	if (data->prec < 0)
	{
		data->flag_neg = -1;
		if ((ft_strchr("piduxX", *data->buff)))
			data->prec = 0;
		if ((ft_strchr("cs%", *data->buff)))
			data->prec *= -1;
	}
}

int			dist_printf(t_data *data)
{
	char	*str;
	int		len_str;
	int		diff_num;

	str = data->var;
	len_str = ft_strlen(str);
	if (data->width < 0 || data->prec < 0)
		neg_width_prec(data);
	diff_num = data->width - data->prec;
	if ((ft_strchr("piduxX", *data->buff)))
		len_str = dist_p_i_d_u_x_x_big(data, *str, len_str, diff_num);
	else if ((ft_strchr("s", *data->buff)))
		len_str = dist_string(data, len_str);
	else if ((ft_strchr("%", *data->buff)))
		len_str = dist_percent(data, len_str, diff_num);
	if ((data->var = (char*)malloc(sizeof(char) * (data->s_arr + 1))) == NULL)
	{
		free(str);
		return (-1);
	}
	fill_array(data, str, len_str, diff_num);
	return (0);
}
