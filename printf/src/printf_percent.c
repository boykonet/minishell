/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:32:13 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/28 16:32:13 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static int	get_data_percent(t_data *data)
{
	if ((data->var = (char*)malloc(sizeof(char) * 2)) == NULL)
		return (-1);
	data->var[0] = '%';
	data->var[1] = '\0';
	return (0);
}

int			percent_with_flags(t_data *data, char ch, va_list ap,
			int (*f)(t_data*))
{
	if (*data->buff != ch)
	{
		if ((checker_printf(data, ap)) == -1)
			return (-1);
	}
	if ((f(data)) == -1)
		return (-1);
	if ((dist_printf(data)) == -1)
		return (-1);
	return (0);
}

int			printf_spec_perc(t_data *data, va_list ap, char ch,
			int (*f)(t_data*))
{
	if (ch != *data->buff)
	{
		if ((percent_with_flags(data, ch, ap, f)) == -1)
			return (-1);
		return (0);
	}
	data->without_flags = 1;
	if ((f(data)) == -1)
		return (-1);
	return (0);
}

int			printf_percent(t_data *data, va_list ap, char *s)
{
	if ((printf_spec_perc(data, ap, *s, &get_data_percent)) == -1)
		return (-1);
	return (0);
}
