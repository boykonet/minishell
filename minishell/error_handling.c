/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 19:35:44 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/31 19:35:44 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "../minishell.h"

int 		error_handling(char *cmd, char *arg, int fd, int status)
{
	if (!ft_strncmp(arg, "cat", ft_strlen(arg)))
		write(fd, "-minishell: ", 12);
	if (status == 258 && arg)
	{
		write(fd, "syntax error near unexpected token `", 36);
		write(fd, arg, ft_strlen(arg));
		write(fd, "'\n", 2);
	}
	else if (status == 127 && arg)
	{
		write(fd, arg, ft_strlen(arg));
		write(fd, ": command not found\n", 20);
	}
	else if (status == 1 && arg)
	{
		if (cmd)
		{
			write(fd, cmd, ft_strlen(cmd));
			write(fd, ": ", 2);
		}
		write(fd, arg, ft_strlen(arg));
		write(fd, ": No such file or directory\n", 28);
	}
	return (status);
}
