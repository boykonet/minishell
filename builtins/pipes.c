/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:33:57 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/10 15:33:57 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "other.h"
#include "minishell.h"

static void		work_child_proc(t_d **data, t_params *par, t_pipes *pp)
{
	if (pipe(pp->rpipe) == -1)
	{
		ft_putendl_fd("-minishell: pipe failed", 2);
		exit(EXIT_FAILURE);
	}
	fork_child_proc(data, par, pp);
	if (pp->position > 0)
	{
		close_fd(pp->lpipe[0]);
		close_fd(pp->lpipe[1]);
	}
	if (pp->position < pp->size_params - 1)
	{
		pp->lpipe[0] = pp->rpipe[0];
		pp->lpipe[1] = pp->rpipe[1];
	}
}

static int		pipes_in_work(t_d **data, t_params **params)
{
	t_pipes		pp;
	t_params	*curr;
	int			status;

	init_pipes(&pp);
	curr = (*params);
	while (curr && curr->pipe_semic == 1)
	{
		pp.size_params++;
		curr = curr->next;
	}
	if (!(pp.childpid = ft_calloc(++pp.size_params, sizeof(pid_t))))
		exit(errno);
	while (pp.position < pp.size_params)
	{
		work_child_proc(data, *params, &pp);
		(*params) = (*params)->next;
		pp.position++;
	}
	close_fd(pp.rpipe[0]);
	close_fd(pp.rpipe[1]);
	status = parent_pipes(&pp);
	free(pp.childpid);
	return (status);
}

int				pipes(t_d **data, t_params **params)
{
	int			status;

	status = pipes_in_work(data, params);
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	(*data)->flag = 0;
	return (status);
}
