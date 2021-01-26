/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:32:32 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:32:32 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	get_data_s(t_data *data, va_list ap)
{
	char	*str;

	str = (char*)va_arg(ap, char*);
	if (str == NULL)
	{
		data->flag_zero = 0;
		if ((data->var = ft_strdup("(null)")) == NULL)
			return (-1);
	}
	else
	{
		if ((data->var = ft_strdup(str)) == NULL)
			return (-1);
	}
	return (0);
}

int			printf_s(t_data *data, va_list ap, char *s)
{
	if ((printf_spec(data, ap, *s, &get_data_s)) == -1)
		return (-1);
	return (0);
}
