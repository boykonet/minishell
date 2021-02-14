/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 09:36:09 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 09:36:09 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"
#include "parser.h"
#include "minishell.h"

int			check_redir(char **line)
{
	char	*curr_str;
	char	*redir;
	int		r;

	redir = NULL;
	curr_str = (*line);
	if (!ft_strncmp(*line, ">>", 2))
		curr_str += 2;
	else if (!ft_strncmp(*line, ">", 1) || \
		!ft_strncmp(*line, "<", 2))
		curr_str += 1;
	if (!(redir = ft_substr((*line), 0, curr_str - (*line))))
		exit(errno);
	r = number_of_redirect(redir);
	free(redir);
	return (r);
}
