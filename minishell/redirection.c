/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:52:21 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 00:52:21 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		redirection(t_flags *f, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (ft_strnstr(arg[i], "<"))
			f->left_redir = 1;
		else if (ft_strnstr(arg[i], ">"))
			f->right_redir = 1;
		else if (ft_strnstr(arg[i], ">>"))
			f->right_dubl_redir = 1;
		i++;
	}
}
