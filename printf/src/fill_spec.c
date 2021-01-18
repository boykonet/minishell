/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:36:11 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:36:11 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	handle_neg_fill(t_data *data, char *str, int len_str, int diff_num)
{
	if (data->sign == 2)
	{
		*data->var = '-';
		ft_memcpy(&data->var[data->s_arr - len_str], &str[1], len_str);
	}
	else if (data->sign == 0)
	{
		data->temp = data->prec < len_str ? len_str : data->prec;
		ft_memset(&data->var[data->s_arr - data->temp], '0', data->temp);
		ft_memcpy(&data->var[data->s_arr - len_str], &str[1], len_str);
		if (data->temp > len_str)
			data->var[diff_num - 1] = '-';
		else
			data->var[data->s_arr - data->temp - 1] = '-';
	}
	else if (data->sign == 1)
	{
		data->temp = data->prec < len_str ? len_str : data->prec;
		*data->var = '-';
		ft_memset(&data->var[1], '0', data->temp);
		ft_memcpy(&data->var[data->temp - len_str + 1], &str[1], len_str);
	}
}

static void	handle_negative(t_data *data, char *str, int len_str, int diff_num)
{
	if (diff_num > 0)
		handle_neg_fill(data, str, len_str, diff_num);
	else
	{
		*data->var = '-';
		ft_memcpy(&data->var[data->s_arr - len_str], &str[1], len_str);
	}
}

static void	percent_check(t_data *data, char *str, int len_str)
{
	if (data->sign == 2)
		ft_memset(data->var, '0', data->s_arr);
	else
		ft_memset(data->var, ' ', data->s_arr);
	if (data->sign == 2 || data->sign == 0)
		ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
	if (data->sign == 1)
		ft_memcpy(data->var, str, len_str);
	data->var[data->s_arr] = '\0';
}

static void	fill_string(t_data *data, char *str, int len_str, int diff_num)
{
	if (diff_num > 0)
	{
		ft_memset(data->var, ' ', data->s_arr);
		data->var[data->s_arr] = '\0';
		if (data->sign == 0 || data->sign == 2)
			ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
		else if (data->sign == 1)
		{
			data->temp = data->prec < len_str ? len_str : data->prec;
			ft_memcpy(&data->var[data->temp - len_str], str, len_str);
		}
	}
	else
	{
		ft_memset(data->var, ' ', data->s_arr);
		data->var[data->s_arr] = '\0';
		if (data->sign == 0 || data->sign == 2)
			ft_memcpy(&data->var[data->s_arr - len_str], str, len_str);
		if (data->sign == 1)
			ft_memcpy(data->var, str, len_str);
	}
}

void		fill_spec(t_data *data, char *str, int len_str, int diff_num)
{
	if (*data->buff == 's')
		fill_string(data, str, len_str, diff_num);
	else if (*data->buff == '%')
		percent_check(data, str, len_str);
	else if (data->n_num == -1)
		handle_negative(data, str, len_str, diff_num);
}
