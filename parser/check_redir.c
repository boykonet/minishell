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

#include "parser.h"
#include "minishell.h"

int			check_redir(char **line)
{
	char	*curr_str;
	char	*str;
	char	symb;
	int		r;
	int 	i;

	r = -1;
	i = 0;
	if (*(*line) == '<' || *(*line) == '>')
	{
		curr_str = (*line);
		symb = *(*line);
		while (i < 2 && *curr_str && *curr_str == symb && *curr_str != ' ')
			curr_str++;
		if (!(str = ft_substr((*line), 0, curr_str - (*line))))
			exit(errno);
		r = number_of_redirect(str);
		free(str);
	}
	return (r);
}
