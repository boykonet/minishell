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
	if (params->cmd)
		free(params->cmd);
	if (params->args)
		ft_lstclear(&params->args, del_content);
	if (params->in > 2)
		close(params->in);
	if (params->out > 2)
		close(params->out);
	if (params->err > 2)
		close(params->err);
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
