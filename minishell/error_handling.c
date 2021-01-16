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

int 		error_handling(char *cmd, char *arg, char *error, int status)
{
	if (!cmd)
		write(2, "-minishell: ", 12);
	else
	{
		write(2, "-minishell: ", 12);
		write(2, "", ft_strlen(cmd));
	}
	if (error)
	{
		if (arg)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
		else
			write(2, error, ft_strlen(error));
	}
	write(2, "\n", 1);
	return (status);
}
