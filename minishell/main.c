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

t_data		*init_data(t_data *data)
{
	data->envp_dupl = NULL;
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

char		**copy_envp(char **envp)
{
	char	**envp_dupl;
	int		envp_size;
	int		i;

	i = 0;
	envp_dupl = NULL;
	envp_size = number_of_lines(envp);
	if (!(envp_dupl = malloc(sizeof(char*) * (size_envp + 1))))
		return (NULL);
	while (envp[i])
	{

	}
}

int			main(int argc, char **argv, char **envp)
{
	t_data	data;

	data = init_data(&data);
	if (!(data.envp_dupl = copy_envp(envp)))
	{
		strerror(errno);
		return (-1);
	}
	return (0);
}
