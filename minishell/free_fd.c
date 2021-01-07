/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:52:41 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/17 22:52:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_fd(t_fd *fd)
{
	if (fd->name_in)
		free(fd->name_in);
	if (fd->name_out)
		free(fd->name_out);
	if (fd->name_err)
		free(fd->name_err);
}
