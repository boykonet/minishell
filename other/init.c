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
	(*params)->pipe_semic = 0;
	(*params)->next = NULL;
}

void		init_pipes(t_pipes *pp)
{
	*pp = (t_pipes) { { 0, 0 }, { 0, 0 }, NULL, 0, 0 };
}

void		init_data(t_d **data)
{
	(*data)->argc = 0;
	(*data)->exit_status = 0;
	(*data)->flag = 0;
	(*data)->origfd[0] = dup(STDIN_FILENO);
	(*data)->origfd[1] = dup(STDOUT_FILENO);
	(*data)->argv = NULL;
	(*data)->env = NULL;
	(*data)->line = NULL;
	(*data)->folder = NULL;
	(*data)->logname = NULL;
	(*data)->home = NULL;
	(*data)->params = NULL;
}

void		init_eval(t_d **data, t_eval *eval, const int *status)
{
	eval->exit_status = (*data)->exit_status == 2 ? 1 : 0;
	eval->dollar_flag = 0;
	eval->env = (*data)->env;
	eval->quotes = 0;
	eval->status = *status;
	eval->home = (*data)->home;
}
