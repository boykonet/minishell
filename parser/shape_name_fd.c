/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_name_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.r       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:38:41 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/10 23:38:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void 	token_with_dollar_error(char *start, char *end, t_parser *p)
{
	char 		*res;

	if (!(res = ft_substr(start, 0, end - start)))
		exit(errno);
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(res, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	free(res);
	p->status = 1;
	p->exit_status = 2;
}

static char		*token_with_dollar(char **line, t_parser *p)
{
	char 		*start;
	char 		*end;
	char 		*res;

	start = (*line);
	end = (*line);
	while (*end && *end != ' ' && *end != '\\')
		end++;
	if (*end == '\\' && *(end + 1))
	{
		start = ++end;
		if (*end == '$')
			end++;
		while (*end && *end != ' ' && *end != '$')
			end++;
		if (!(res = ft_substr(start, 0, end - start)))
			exit(errno);
		while (*end && *end != ' ')
			end++;
		(*line) = end;
		return (res);
	}
	else
		token_with_dollar_error(start, end, p);
	return (NULL);
}

char			*shape_name_fd(char **line, char *curr, t_parser *p)
{
	char		symb;
	char		*name_fd;

	symb = *(*line);
	name_fd = NULL;
	if (*curr == '$')
		name_fd = token_with_dollar(line, p);
	else if (*curr == ';' || *curr == '|')
	{
		while (*curr && *curr == symb && *curr != ' ')
			curr++;
		if (!(name_fd = ft_substr((*line), 0, curr - *(line))))
			exit(errno);
		(*line) = curr;
	}
	else
		name_fd = return_token(line, p);
	return (name_fd);
}
