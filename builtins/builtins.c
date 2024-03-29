/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:57:36 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/07 15:29:16 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"

static int	seven_commands(t_d **data, t_params *params)
{
	int		stat;

	stat = 0;
	if (!ft_strcmp(params->args->content, "echo"))
		stat = ft_echo(params->args->next);
	else if (!ft_strcmp(params->args->content, "pwd"))
		stat = ft_pwd();
	else if (!ft_strcmp(params->args->content, "cd"))
		stat = ft_cd(params->args->next, &(*data)->env);
	else if (!ft_strcmp(params->args->content, "export"))
		stat = ft_export(&(*data)->env, params);
	else if (!ft_strcmp(params->args->content, "unset"))
		stat = ft_unset(&(*data)->env, params);
	else if (!ft_strcmp(params->args->content, "env"))
		stat = ft_env(&(*data)->env, params);
	else if (!ft_strcmp(params->args->content, "exit"))
		stat = ft_exit(params->args->next, &(*data)->exit_status);
	return (stat);
}

int			builtins(t_d **data, t_params *params)
{
	int		status;

	status = 0;
	if (!find_data_in_env((*data)->env, "PATH", 0) && \
	!ft_strcmp(params->args->content, "env"))
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(params->args->content, 2);
		ft_putendl_fd(": No such file or directory", 2);
		status = 127;
		(*data)->exit_status = 2;
	}
	if (!status)
		status = seven_commands(data, params);
	return (status);
}
