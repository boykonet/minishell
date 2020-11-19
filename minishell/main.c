/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:15:41 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 16:15:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		init_data(t_data *data)
{
	data->envp_dupl = NULL;
	data->envp_size = 0;
	data->redir_double_rigth = 0;
	data->redir_left = 0;
	data->redir_rigth = 0;
}

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void		free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

char		**copy_str(char **str, int str_size)
{
	char	**str_dupl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_dupl = NULL;
	if (!(str_dupl = malloc(sizeof(char*) * (str_size + 1))))
		return (NULL);
	str_dupl[str_size] = NULL;
	while (str[i])
	{
		if (!(str_dupl[j] = malloc(sizeof(char) * ft_strlen(str[i]))))
		{
			free_str(str_dupl);
			return (NULL);
		}
		i++;
		j++;
	}
	return (str_dupl);
}

int			main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data);
	data.envp_size = number_of_lines(envp);
	if (!(data.envp_dupl = copy_str(envp, data.envp_size)))
	{
		strerror(errno);
		return (-1);
	}
	while (TRUE)
	{
		gnl();
		parser(&data);
	}
	return (0);
}
