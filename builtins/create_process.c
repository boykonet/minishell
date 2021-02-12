/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:25:30 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/07 15:26:20 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "other.h"

static int	child_process(t_params *par, char **args, char **envp, char *cmd)
{
	int		exit_code;

	exit_code = 0;
	if (par->in > 2)
		dup2(par->in, 0);
	if (par->out > 2)
		dup2(par->out, 1);
	if (execve(cmd, args, envp) < 0)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit_code = 127;
	}
	exit(exit_code);
}

static int	parent_process(int pid, t_d **data)
{
	int		wstatus;
	int		status_code;

	wstatus = 0;
	status_code = 0;
	(*data)->flag = 1;
	if (waitpid(pid, &wstatus, WUNTRACED) < 0)
	{
		ft_putendl_fd("-minishell: waitpid failed", 2);
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(wstatus) > 0)
		status_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		status_code = 128 + WTERMSIG(wstatus);
	return (status_code);
}

int			create_process(t_d **data, char **args, char **envp, char *cmd)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == 0)
		child_process((*data)->params, args, envp, cmd);
	else if (pid < 0)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
	status = parent_process(pid, data);
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	(*data)->flag = 0;
	return (status);
}
