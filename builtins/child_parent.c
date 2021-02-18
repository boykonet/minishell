/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:23:01 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 01:23:01 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "builtins.h"

static int		write_in_fd(t_d **data, t_params *par, char **args, \
									char **envp)
{
	int			status;
	char		*cmd;

	status = 0;
	cmd = name_cmd(data, par, &status);
	if (status > 0)
		return (status);
	if (!check_command(cmd))
		status = builtins(data, par);
	else
	{
		if (execve(cmd, args, envp) < 0)
			execve_error(cmd, &status);
	}
	free(cmd);
	return (status);
}

static int		cmd_write(t_d **data, t_params *par, t_pipes *pp)
{
	int			status;
	char		**envp;
	char		**args;

	if (par->in > 2)
		dup2(par->in, 0);
	if (par->out > 2)
		dup2(par->out, 1);
	else if (pp->position < pp->size_params - 1)
		dup2(pp->rpipe[1], 1);
	close_fd(pp->rpipe[0]);
	close_fd(pp->rpipe[1]);
	envp = convert_env_to_arr((*data)->env);
	args = convert_struct_to_array(par->args);
	status = write_in_fd(data, par, args, envp);
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

void			fork_child_proc(t_d **data, t_params *par, t_pipes *pp)
{
	int			status;

	if (!((pp->childpid[pp->position]) = fork()))
	{
		if (pp->position > 0)
			cmd_read(data, pp->lpipe);
		status = cmd_write(data, par, pp);
		exit(status);
	}
	if ((pp->childpid[pp->position]) < 0)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
}

int				parent_pipes(t_pipes *pp)
{
	int			status;
	int			i;

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
