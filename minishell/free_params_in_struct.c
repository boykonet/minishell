/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params_in_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:55:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/17 22:55:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_params(t_params *params)
{
	if (params->args)
		ft_lstclear(&params->args, &del_content);
	if (params->command)
		free(params->command);
	if (params->flags)
		free(params->flags);
	if (params->redir)
		free(params->redir);
	if (params->name_fd)
		free(params->name_fd);
}

void		free_fd(t_fd *fd)
{
	if (fd->in)
		free(fd->in);
	if (fd->out)
		free(fd->out);
	if (fd->err)
		free(fd->err);
}

void		free_string(char **str)
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
