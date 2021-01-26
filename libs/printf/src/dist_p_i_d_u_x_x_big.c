/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_p_i_d_u_x_x_big.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:30:57 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/29 17:30:57 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	zero_check_number(t_data *data, int len_str, int diff_num)
{
	if (diff_num > 0)
	{
		if (data->flag_neg == -1 && data->sign == 2)
			data->prec = data->width;
		else
		{
			if (data->flag_neg == -1)
				data->prec = len_str;
			len_str = data->prec;
		}
		data->s_arr = data->width;
	}
	else
	{
		if (data->flag_neg == -1)
			data->prec = len_str;
		else
			len_str = data->width;
		data->s_arr = data->prec;
	}
	return (len_str);
}

static int	diff_num_positive(t_data *data, char ch, int len_str, int diff_num)
{
	if (data->prec == 0 && ch == '0' && len_str == 1 && data->dot == 1)
		len_str = zero_check_number(data, len_str, diff_num);
	else
	{
		if (data->flag_neg == -1 && data->sign == 2)
			data->prec = data->width;
		data->s_arr = data->width;
		if (len_str > data->width && data->n_num == 1)
			data->s_arr = len_str;
		if (len_str >= data->width && data->n_num == -1)
			data->s_arr = len_str + 1;
	}
	return (len_str);
}

static int	diff_num_negative(t_data *data, char ch, int len_str, int diff_num)
{
	if (data->prec == 0 && ch == '0' && len_str == 1 && data->dot == 1)
		len_str = zero_check_number(data, len_str, diff_num);
	else
	{
		if (data->flag_neg == -1 && data->sign == 2)
			data->prec = data->width;
		if (len_str > data->prec)
			data->prec = len_str;
		data->s_arr = data->prec;
		if (data->n_num == -1)
			data->s_arr++;
	}
	return (len_str);
}

int			dist_p_i_d_u_x_x_big(t_data *data, char ch, int len_str,
			int diff_num)
{
	if (ch == '-')
	{
		data->n_num = -1;
		len_str--;
	}
	if (diff_num > 0)
		len_str = diff_num_positive(data, ch, len_str, diff_num);
	else
		len_str = diff_num_negative(data, ch, len_str, diff_num);
	return (len_str);
}
