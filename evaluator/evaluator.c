/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 02:03:59 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 02:03:59 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluator.h"
#include "utils.h"

static void			redefinition(t_d **data, t_eval *eval, int *status)
{
	if (eval->status > 0 && eval->exit_status == 1)
	{
		eval->status = 0;
		eval->exit_status = 0;
	}
	(*data)->exit_status = eval->exit_status;
	*status = eval->status;
}

void				evaluator(t_d **data, t_params **par, int *status)
{
	t_eval			eval;
	t_params		*curr;
	t_params		*next;

	init_eval(data, &eval, status);
	curr = (*par);
	while (curr)
	{
		next = curr->next;
		check_lists(curr, &eval);
		if (!curr->args)
		{
			params_delete(&(*data)->params, curr);
			(*par) = next;
		}
		else if (eval.exit_status == 2)
			break ;
		curr = next;
	}
	redefinition(data, &eval, status);
}
