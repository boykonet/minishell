/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:13:02 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/24 18:13:02 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "evaluator.h"
#include "minishell.h"

static void		redirect_and_name_fd(char *redir, char *name, \
				t_eval *eval, int *fd)
{
	char		*nfd;

	nfd = shape_name_fd(name, eval);
	if (eval->exit_status != 2)
	{
		if ((*fd = open_fd(nfd, redir)) < 0)
		{
			eval->status = 1;
			eval->exit_status = 2;
		}
	}
	free(nfd);
}

static void		reopen_fd(char *redir, char *name, t_eval *eval, int *fd)
{
	if (*fd > 2)
	{
		close_fd(*fd);
		*fd = -2;
	}
	redirect_and_name_fd(redir, name, eval, fd);
}

void			open_and_close_fd(char *redir, char *name, \
				t_eval *eval, t_params **params)
{
	if (number_of_redirect(redir) == 0)
		reopen_fd(redir, name, eval, &((*params)->in));
	else if (number_of_redirect(redir) == 1)
		reopen_fd(redir, name, eval, &((*params)->out));
	else if (number_of_redirect(redir) == 2)
		reopen_fd(redir, name, eval, &((*params)->err));
}
