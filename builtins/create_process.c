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

char			*find_cmd(t_d **data, t_params *par, int *status)
{
	char		*cmd;

	cmd = find_path(par->args->content,\
	find_data_in_env((*data)->env, "PATH", 0), status);
	if (!cmd && !(*status))
		cmd = ft_strdup(par->args->content);
	return (cmd);
}

void			execve_error(char *cmd, int *status)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	if (errno == 13)
		*status = 126;
	else if (errno == 2)
		*status = 127;
}

static int		child_process(t_params *par, char **args, \
				char **envp, char *cmd)
{
	int			exit_code;

	exit_code = 0;
	if (par->in > 2)
		dup2(par->in, 0);
	if (par->out > 2)
		dup2(par->out, 1);
	if (execve(cmd, args, envp) < 0)
		execve_error(cmd, &exit_code);
	exit(exit_code);
}

static int		parent_process(int pid, t_d **data)
{
	int			wstatus;
	int			status_code;

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

int				create_process(t_d **data, t_params *par, \
				char **args, char **envp)
{
	pid_t		pid;
	char		*cmd;
	int			status;

	status = 0;
	cmd = find_cmd(data, par, &status);
	if (status > 0)
		return (status);
	if ((pid = fork()) == -1)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(par, args, envp, cmd);
	else
		status = parent_process(pid, data);
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	(*data)->flag = 0;
	free(cmd);
	return (status);
}
