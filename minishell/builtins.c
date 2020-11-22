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

#include "../minishell.h"

void		builtins(t_params *params, char **home, char **pwd_curr, char **old_pwd)
{
	char	*str;

	str = NULL;
	if (!ft_strncmp(str->command, "echo", 4))
		str = ft_echo(params, fd, envp);

	else if (!ft_strncmp(str->command, "pwd", 3))
		str = ft_pwd(params->args);

	else if (!ft_strncmp(str->command, "cd", 2))
		str = ft_cd(params->args, home, pwd_curr, old_pwd);

	else if (!ft_strncmp(str->command, "export", 6))
		ft_export();

	else if (!ft_strncmp(str->command, "unset", 5))
		ft_unset();

	else if (!ft_strncmp(str->command, "env", 3))
		ft_env();

	else if (!ft_strncmp(str->command, "exit", 4))
		ft_exit();
}
