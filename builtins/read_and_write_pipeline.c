/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:56:08 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/07 15:56:41 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		read_and_write_pipeline(int *origfd)
{
	char	buff[101];
	char	*tmp;
	char	*line;
	int		len;

	line = ft_strdup("");
	while ((len = read(0, buff, 100)) > 0)
	{
		tmp = line;
		buff[len] = '\0';
		if (!(line = ft_strjoin(line, buff)))
			exit(errno);
		free(tmp);
	}
	dup2(origfd[0], 0);
	dup2(origfd[1], 1);
	ft_putstr_fd(line, 1);
	free(line);
}
