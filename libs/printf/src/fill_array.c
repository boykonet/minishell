/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:35:54 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:35:54 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void		fill_array(t_data *data, char *str, int len_str, int diff_num)
{
	if ((ft_strchr("cpiduxX%", *data->buff)))
		fill_c_p_i_d_u_x_x_big_prc(data, str, len_str, diff_num);
	else if ((ft_strchr("s", *data->buff)))
		fill_spec(data, str, len_str, diff_num);
	free(str);
}
