/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:31:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 15:31:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ft_pwd(void)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd("-minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
