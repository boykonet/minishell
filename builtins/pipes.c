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

static int		write_in_fd(t_d **data, t_params *curr, char **args, \
									char **envp)
{
	int			status;
	char		*cmd;

	status = 0;
	cmd = NULL;
	if (!(cmd = find_path(curr->args->content, \
	find_data_in_env((*data)->env, "PATH", 0), &status)))
		if (!status)
			if (!(cmd = ft_strdup(curr->args->content)))
				exit(EXIT_FAILURE);
	if (!status && !check_command(curr->args->content))
		status = builtins(data, curr);
	else if (!status)
	{
		if (execve(cmd, args, envp) < 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			status = 127;
		}
	}
	free(cmd);
	return (status);
}

static int		cmd_write(t_d **data, t_params *curr, t_pipes *pp)
{
	int			status;
	char		**envp;
	char		**args;

	if (curr->in > 2)
		dup2(curr->in, 0);
	if (curr->out > 2)
		dup2(curr->out, 1);
	else if (pp->position < pp->size_params - 1)
		dup2(pp->rpipe[1], 1);
	close_fd(pp->rpipe[0]);
	close_fd(pp->rpipe[1]);
	envp = convert_env_to_arr((*data)->env);
	args = convert_struct_to_array(curr->args);
	status = write_in_fd(data, curr, args, envp);
	free_string(args);
	free_string(envp);
	return (status);
}

static void		cmd_read(t_d **data, int *lpipe)
{
	(*data)->flag = 1;
	dup2(lpipe[0], 0);
	close_fd(lpipe[0]);
	close_fd(lpipe[1]);
}

static void		fork_child_proc(t_d **data, t_params *curr, t_pipes *pp)
{
	int 		status;

	if (!((pp->childpid[pp->position]) = fork()))
	{
		if (pp->position > 0)
			cmd_read(data, pp->lpipe);
		status = cmd_write(data, curr, pp);
		exit(status);
	}
	if ((pp->childpid[pp->position]) < 0)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
}

static int 		parent_pipes(t_pipes *pp)
{
	int 		status;
	int 		i;

	i = 0;
	status = 0;
	while (i < pp->size_params)
	{
		if (waitpid(pp->childpid[i], &status, WUNTRACED) < 0)
		{
			ft_putstr_fd("-minishell: waitpid: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
	return (status);
}

static void 	work_child_proc(t_d **data, t_params *curr, t_pipes *pp)
{
	if (pipe(pp->rpipe) == -1)
	{
		ft_putendl_fd("-minishell: pipe failed", 2);
		exit(EXIT_FAILURE);
	}
	fork_child_proc(data, curr, pp);
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

static int		pipes_in_work(t_d **data, t_params **par)
{
	t_pipes 	pp;
	t_params	*curr;
	int			status;

	init_pipes(&pp);
	curr = (*par);
	while (curr && curr->pipe_semic == 1)
	{
		curr = curr->next;
		pp.size_params++;
	}
	if (!(pp.childpid = ft_calloc(++pp.size_params, sizeof(pid_t))))
		exit(errno);
	while ((*par) && pp.position < pp.size_params)
	{
		work_child_proc(data, (*par), &pp);
		(*par) = (*par)->next;
		pp.position++;
	}
	close_fd(pp.rpipe[0]);
	close_fd(pp.rpipe[1]);
	status = parent_pipes(&pp);
	free(pp.childpid);
	return (status);
}

int				pipes(t_d **data, t_params **par)
{
	int			status;

	status = pipes_in_work(data, par);
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	(*data)->flag = 0;
	return (status);
}
