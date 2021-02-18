/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:30:33 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 15:30:33 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				spec_symb(int quotes, int escaping, int ident, char c)
{
	if (!quotes && (c == ' ' || c == '\0' || c == '\t') && !escaping)
		return (1);
	else if ((!ident || ident == 1) && !quotes && (c == ';' || c == '|') && \
	!escaping)
		return (2);
	else if (!ident && !quotes && (c == '>' || c == '<') && !escaping)
		return (3);
	else if (!ident && !quotes && (c == ')' || c == '(' || c == '&') && \
	!escaping)
		return (4);
	return (0);
}

static void		esc_quotes(t_lexic *lexic, char c)
{
	if (c == '\\' && lexic->escaping == 0)
		lexic->escaping = 1;
	else if (c == '\\' && lexic->escaping == 1)
		lexic->escaping = 2;
	if (c == '\'' && lexic->quotes == 0)
		lexic->quotes = 1;
	else if (c == '\'' && lexic->quotes == 1)
		lexic->quotes = 2;
	if (c == '\"' && lexic->escaping == 0 && lexic->quotes == 0)
		lexic->quotes = 1;
	else if (c == '\"' && lexic->escaping == 0 && lexic->quotes == 1)
		lexic->quotes = 2;
}

int				lexic_token(char **line, int ident)
{
	t_lexic		lexic;
	int			r;
	char		c;

	lexic.escaping = 0;
	lexic.quotes = 0;
	c = *(*line);
	while (c)
	{
		if ((r = spec_symb(lexic.quotes, lexic.escaping, ident, c)))
			return (r);
		esc_quotes(&lexic, c);
		if ((lexic.escaping == 1 && c != '\\') || lexic.escaping == 2)
			lexic.escaping = 0;
		if (lexic.quotes == 2)
			lexic.quotes = 0;
		(*line)++;
		c = *(*line);
	}
	return (0);
}
