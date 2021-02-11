/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unexpected_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:35:29 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/10 23:35:29 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

int				check_unexpected_token(char *token, t_parser *p)
{
	char		**err;
	int			i;

	i = 0;
	err = (char*[]) {">>", "<<", ";;", "||", "<", ">", "(", ")", ";", \
						"|", "", NULL};
	while (err[i])
	{
		if (*token == *err[i] && \
		!ft_strncmp(err[i], token, ft_strlen(err[i])) && \
		!ft_isalpha(*(token + ft_strlen(err[i]))))
		{
			ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
			if (!ft_strncmp(token, "", 1))
				ft_putstr_fd("newline", 2);
			else
				ft_putstr_fd(err[i], 2);
			ft_putendl_fd("'", 2);
			p->status = 258;
			p->exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}
