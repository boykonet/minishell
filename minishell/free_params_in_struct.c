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
//	if (params->redir_in)
//		free(params->redir_in);
//	if (params->redir_out)
//		free(params->redir_out);
//	if (params->redir_err)
//		free(params->redir_err);
//	if (params->name_in)
//		free(params->name_in);
//	if (params->name_out)
//		free(params->name_out);
//	if (params->name_err)
//		free(params->name_err);
}

//void		free_fd(t_fd *fd)
//{
//	if (fd->redir_in)
//		free(fd->redir_in);
//	if (fd->redir_out)
//		free(fd->redir_out);
//	if (fd->redir_err)
//		free(fd->redir_err);
//	if (fd->name_in)
//		free(fd->name_in);
//	if (fd->name_out)
//		free(fd->name_out);
//	if (fd->name_err)
//		free(fd->name_err);
//
//	if (fd->in > 2)
//		close(fd->in);
//	if (fd->out > 2)
//		close(fd->out);
//	if (fd->err > 2)
//		close(fd->err);
//}

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
