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

/* -minishell: cd: ,: No such file or directory */
-bash: fhfhfh.txt: No such file or directory
		cat: ttt.txt: No such file or directory
		grep: minishell: Is a directory

void		error_handling(char *cmd, char *str, int spec, int err)
{
	if (spec > 0)
		write(err, "-minishell: ", 12);
	else
		write(err, cmd, ft_strlen(cmd));
	if (spec == 1 && str)
	{
		write(err, "syntax error near unexpected token `", 36);
		write(err, str, ft_strlen(str));
		wtite(err, "'\n", 2);
	}
	else if (spec == 2 && str)
	{
		write(err, str, ft_strlen(str));
		write(err, ": command not found\n", 20);
	}
	else if (spec == 3 && str)
	{
		if (cmd)
		{
			write(err, cmd, ft_strlen(cmd));
			write(err, ": ", 2);
		}
		write(err, str, ft_strlen(str));
		write(err, ": No such file or directory\n", 28);
	}
	else if ()

}
