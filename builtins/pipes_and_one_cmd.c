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
#include "utils.h"
#include "builtins.h"

static int		one_cmd_builtins(t_d **data, t_params **par)
{
	int			status;

	if ((*par)->in > 2)
		dup2((*par)->in, 0);
	if ((*par)->out > 2)
		dup2((*par)->out, 1);
	status = builtins(data, *par);
	dup2((*data)->origfd[0], 0);
	dup2((*data)->origfd[1], 1);
	if (status > 0 && (*data)->exit_status != 1)
		(*data)->exit_status = 2;
	return (status);
}

static int		one_cmd_execve(t_d **data, t_params **par)
{
	char		**arr;
	char		**envp;
	int			status;

	arr = convert_struct_to_array((*par)->args);
	envp = convert_env_to_arr((*data)->env);
	status = create_process(data, *par, arr, envp);
	free_string(arr);
	free_string(envp);
	if (status > 0)
		(*data)->exit_status = 2;
	return (status);
}

int				pipes_and_one_cmd(t_d **data, t_params *par, int *status)
{
	if (par && par->pipe_semic == 1)
	{
		*status = pipes(data, &par);
		if (*status > 0)
			(*data)->exit_status = 2;
	}
	else if (par)
	{
		if (!check_command(par->args->content))
			*status = one_cmd_builtins(data, &par);
		else
			*status = one_cmd_execve(data, &par);
		if (!ft_strcmp(par->args->content, "exit") && \
				(*data)->exit_status == 1)
			return (0);
	}
	return (1);
}
