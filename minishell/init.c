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

void		init_params(t_params *params)
{
	params->cmd = NULL;
	params->args = NULL;
//	params->redir_in = NULL;
//	params->redir_out = NULL;
//	params->redir_err = NULL;
//	params->name_in = NULL;
//	params->name_out = NULL;
//	params->name_err = NULL;
}

void		init_fd(t_fd *fd)
{
	fd->redir_in = NULL;
	fd->redir_out = NULL;
	fd->redir_err = NULL;
	fd->name_in = NULL;
	fd->name_out = NULL;
	fd->name_err = NULL;
	fd->in = 0;
	fd->out = 1;
	fd->err = 2;
}
