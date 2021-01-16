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
	if (!cmd)
		write(2, "-minishell: ", 12);
	else
	{
		write(2, "-minishell: ", 12);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (error)
	{
		if (arg && num == 1)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
		else if (num == 2)
		{
			write(2, error, ft_strlen(error));
			write(2, " `", 2);
			write(2, arg, ft_strlen(arg));
			write(2, "'", 1);
			status = 258;
		}
	}
	write(2, "\n", 1);
	return (status);
}
