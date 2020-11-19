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

void		builtins(t_str *str, int fd, char *envp)
{
	if (!ft_strncmp(str->command, "echo", 4))
		ft_echo(str->args, fd, envp);

	else if (!ft_strncmp(str->command, "pwd", 3))
		ft_pwd(str->args, fd, envp);

	else if (!ft_strncmp(str->command, "cd", 2))
		ft_cd(str->args, fd, envp);

	else if (!ft_strncmp(str->command, "export", 6))
		ft_export();

	else if (!ft_strncmp(str->command, "unset", 5))
		ft_unset();

	else if (!ft_strncmp(str->command, "env", 3))
		ft_env();

	else if (!ft_strncmp(str->command, "exit", 4))
		ft_exit();
}
