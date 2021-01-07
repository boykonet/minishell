/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:56:08 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/22 22:56:08 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		init_params(t_params *params)
{
	params->args = NULL;
	params->cmd = NULL;
	params->redir_in = NULL;
	params->redir_out = NULL;
	params->redir_err = NULL;
	params->name_in = NULL;
	params->name_out = NULL;
	params->name_err = NULL;
}
