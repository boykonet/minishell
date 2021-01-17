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

int 		error_handling(char *cmd, char *arg, char *error, int num)
{
	int 	status;

	status = 0;
	if (!cmd)
		write(1, "-minishell: ", 12);
	else
	{
		write(1, "-minishell: ", 12);
		write(1, cmd, ft_strlen(cmd));
		write(1, ": ", 2);
	}
	if (error)
	{
		if (arg && num == 1)
		{
			write(1, arg, ft_strlen(arg));
			write(1, ": ", 2);
			write(1, error, ft_strlen(error));
			status = 1;
		}
		else if (arg && num == 2)
		{
			write(1, error, ft_strlen(error));
			write(1, " `", 2);
			write(1, arg, ft_strlen(arg));
			write(1, "'", 1);
			status = 258;
		}
	}
	write(1, "\n", 1);
	return (status);
}
