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
#include "other.h"

static int	seven_commands(t_params *params, t_env **env, int *exit_status)
{
	char	*str;
	int		stat;

	str = NULL;
	stat = 0;
	if (!ft_strcmp(params->args->content, "echo"))
		stat = ft_echo(params->args->next);
	else if (!ft_strcmp(params->args->content, "pwd"))
		stat = ft_pwd(&str);
	else if (!ft_strcmp(params->args->content, "cd"))
		stat = ft_cd(params->args->next, env);
	else if (!ft_strcmp(params->args->content, "export"))
		stat = ft_export(env, params);
	else if (!ft_strcmp(params->args->content, "unset"))
		stat = ft_unset(env, params);
	else if (!ft_strcmp(params->args->content, "env"))
		stat = ft_env(env, params);
	else if (!ft_strcmp(params->args->content, "exit"))
		stat = ft_exit(params->args->next, exit_status);
	if (str)
	{
		ft_putendl_fd(str, 1);
		free(str);
	}
	return (stat);
}

int			builtins(t_d **data)
{
	int		status;

	status = 0;
	if (!find_data_in_env((*data)->env, "PATH", 0) && !ft_strcmp((*data)->params->args->content, "env"))
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd((*data)->params->args->content, 2);
		ft_putendl_fd(": No such file or directory", 2);
		status = 127;
		(*data)->exit_status = 2;
	}
	if (!status)
		status = seven_commands((*data)->params, &(*data)->env, &(*data)->exit_status);
	return (status);
}
