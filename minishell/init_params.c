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
	params->command = NULL;
	params->flags = NULL;
	params->redir = NULL;
	params->name_fd = NULL;
}
