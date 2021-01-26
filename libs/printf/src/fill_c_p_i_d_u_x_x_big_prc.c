/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_c_p_i_d_u_x_x_big_prc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:21 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/29 17:38:21 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	without_flags(t_data *data, char *str, int len_str, int diff_num)
{
	if (data->n_num == 1)
	{
		ft_memset(&data->var[data->s_arr - data->prec], '0', data->prec);
		ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
	}
	else
		fill_spec(data, str, len_str, diff_num);
}

static void	minus_flag(t_data *data, char *str, int len_str, int diff_num)
{
	if (data->n_num == 1)
	{
		data->temp = data->prec < len_str ? len_str : data->prec;
		ft_memset(data->var, '0', data->temp);
		ft_memcpy(&data->var[data->temp - len_str], str, len_str);
	}
	else
		fill_spec(data, str, len_str, diff_num);
}

static void	zero_flag(t_data *data, char *str, int len_str, int diff_num)
{
	if (data->dot == 0)
	{
		ft_memset(data->var, '0', data->s_arr);
		if (data->n_num == 1)
			ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
		else
			fill_spec(data, str, len_str, diff_num);
	}
	else
	{
		if (data->n_num == -1 && data->flag_neg == -1)
			fill_spec(data, str, len_str, diff_num);
		else
			data->sign = 0;
	}
}

static void	fill_num_posit(t_data *data, char *str, int len_str, int diff_num)
{
	if (data->flag_neg == -1 && data->sign == 2)
		ft_memset(data->var, '0', data->s_arr);
	else
		ft_memset(data->var, ' ', data->s_arr);
	data->var[data->s_arr] = '\0';
	if (data->sign == 2)
		zero_flag(data, str, len_str, diff_num);
	if (data->sign == 0)
		without_flags(data, str, len_str, diff_num);
	else if (data->sign == 1)
		minus_flag(data, str, len_str, diff_num);
}

void		fill_c_p_i_d_u_x_x_big_prc(t_data *data, char *str, int len_str,
			int diff_num)
{
	if (diff_num > 0)
		fill_num_posit(data, str, len_str, diff_num);
	else
	{
		if (*data->buff == '%')
			fill_spec(data, str, len_str, diff_num);
		else
		{
			ft_memset(data->var, '0', data->s_arr);
			data->var[data->s_arr] = '\0';
			if (data->n_num == 1)
				ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
			else
				fill_spec(data, str, len_str, diff_num);
		}
	}
}
