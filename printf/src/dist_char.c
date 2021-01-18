/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:01:39 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/29 13:01:39 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	neg_width_char(t_data *data)
{
	if (data->width < 0)
	{
		data->sign = 1;
		data->width *= -1;
	}
}

static void	fill_char(t_data *data, int len_c, int diff_num)
{
	if (diff_num > 0)
	{
		ft_memset(data->var, ' ', data->s_arr);
		data->var[data->s_arr] = '\0';
		if (data->sign == 0)
			data->var[data->s_arr - len_c] = data->c;
		else if (data->sign == 1)
			*data->var = data->c;
	}
	else
	{
		*data->var = data->c;
		data->var[data->s_arr] = '\0';
	}
}

int			dist_char(t_data *data)
{
	int		diff_num;
	int		len_c;

	if (data->width < 0)
		neg_width_char(data);
	diff_num = data->width - data->prec;
	len_c = 1;
	if (diff_num > 0)
	{
		data->prec = len_c;
		data->s_arr = data->width;
	}
	else
	{
		data->prec = len_c;
		data->s_arr = data->dot == 0 ? len_c : data->prec;
	}
	if ((data->var = (char*)malloc(sizeof(char) * (data->s_arr + 1))) == NULL)
		return (-1);
	fill_char(data, len_c, diff_num);
	return (0);
}
