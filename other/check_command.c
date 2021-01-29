/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:25:38 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/29 18:25:38 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_command(char *cmd)
{
	char 	*arr[] = {"echo", "pwd", "cd", "env", "export", "unset", \
						"exit", NULL};
	int 	count;

	count = 0;
	while (arr[count])
	{
		if (!ft_strncmp(arr[count], cmd, ft_strlen(cmd)))
			return (0);
		count++;
	}
	return (1);
}
