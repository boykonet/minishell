/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:57:36 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 20:57:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "other.h"

static int	seven_commands(t_params *params, t_env **env, int *exit_status)
{
	char 	*str;
	int 	stat;

	str = NULL;
	stat = 0;
	if (!ft_strcmp(params->args->content, "echo"))
		stat = ft_echo(params->args->next, params->out);
	else if (!ft_strcmp(params->args->content, "pwd"))
		stat = ft_pwd(&str);
	else if (!ft_strcmp(params->args->content, "cd"))
		stat = ft_cd(params->args->next, env, params->out);
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
		ft_putendl_fd(str, params->out);
		free(str);
	}
	return (stat);
}

int         builtins(t_d **data, t_params *params)
{
	int 	status;

	status = 0;
	if (!find_data_in_env((*data)->env, "PATH", 0))
	{
		ft_putstr_fd("-minishell: ", 1);
		ft_putstr_fd((*data)->params->args->content, 1);
		ft_putendl_fd(": command not found", 1);
		status = 127;
	}
	if (!status)
		status = seven_commands(params, &(*data)->env, &(*data)->exit_status);
	return (status);
}