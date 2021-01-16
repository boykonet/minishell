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

#include "../minishell.h"

t_params	*init_params(t_params *params)
{
	params->args = NULL;
	params->in = 0;
	params->out = 1;
	params->err = 2;
	params->next = NULL;
	return (params);
}

t_data 		*init_data(t_data *data)
{
	data->argc = 0;
	data->argv = NULL;
	data->env = NULL;
	data->line = NULL;
	data->params = NULL;
	return (data);
}