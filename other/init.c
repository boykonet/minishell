/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 20:02:04 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/08 20:02:04 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

void		init_params(t_params **params)
{
	(*params)->args = NULL;
	(*params)->in = 0;
	(*params)->out = 1;
	(*params)->err = 2;
	(*params)->next = NULL;
}

void		init_data(t_d *data)
{
	data->argc = 0;
	data->argv = NULL;
	data->env = NULL;
	data->line = NULL;
	data->folder = NULL;
	data->user_name = NULL;
	data->params = NULL;
}