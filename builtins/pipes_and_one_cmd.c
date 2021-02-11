/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_one_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:48:36 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/11 18:48:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"
#include "builtins.h"

static int		one_cmd_builtins(t_d **data)
{
	int			status;

	if ((*data)->params->in > 2)
		dup2((*data)->params->in, 0);
	if ((*data)->params->out > 2)
		dup2((*data)->params->out, 1);
	status = builtins(data, (*data)->params);
	if (status > 0 && (*data)->exit_status != 1)
		(*data)->exit_status = 2;
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	return (status);
}

static int		one_cmd_execve(t_d **data)
{
	char		**arr;
	char		**envp;
	char		*cmd;
	int			status;

	status = 0;
	arr = convert_struct_to_array((*data)->params->args);
	envp = convert_env_to_arr((*data)->env);
	if (!(cmd = find_path((*data)->params->args->content,\
		find_data_in_env((*data)->env, "PATH", 0), &status)))
		if (!status)
			if (!(cmd = ft_strdup((*data)->params->args->content)))
				exit(errno);
	if (!status)
		status = create_process(data, arr, envp, cmd);
	if (status > 0)
		(*data)->exit_status = 2;
	free_string(arr);
	free_string(envp);
	free(cmd);
	return (status);
}

int				pipes_and_one_cmd(t_d **data, int *status)
{
	if ((*data)->params && (*data)->params->next)
	{
		*status = pipes(data);
		if (*status > 0)
			(*data)->exit_status = 2;
	}
	else if ((*data)->params)
	{
		if (!check_command((*data)->params->args->content))
			*status = one_cmd_builtins(data);
		else
			*status = one_cmd_execve(data);
		if (!ft_strcmp((*data)->params->args->content, "exit") && \
				(*data)->exit_status == 1)
			return (0);
	}
	return (1);
}
