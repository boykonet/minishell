/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:23:20 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 15:23:20 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

char		*remove_spaces(char *line)
{
	while (*line && *line == ' ')
		line++;
	return (line);
}

char		**copy_array(char **src)
{
	char	**res;
	int		i;

	i = number_of_lines(src);
	if (!(res = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	while (src[i])
	{
		if (!(res[i] = ft_strdup(src[i])))
		{
			free_string(res);
			exit(errno);
		}
		i++;
	}
	return (res);
}

void			close_fd(int fd)
{
	if (close(fd) < 0)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd("close: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(errno);
	}
}
