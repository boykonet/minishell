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

static void 	token_with_dollar_error(char *start, char *end, t_eval *eval)
{
	char 		*res;

	if (!(res = ft_substr(start, 0, end - start)))
		exit(errno);
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(res, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	free(res);
	eval->status = 1;
	eval->exit_status = 2;
}

static char		*token_with_dollar(char *line, t_eval *eval)
{
	char 		*end;
	char 		*res;

	end = line;
	res = NULL;
	while (*end && *end != ' ' && *end != '\\')
		end++;
	if (*end == '\\' && *(end + 1))
	{
		line = ++end;
		if (*end == '$')
			end++;
		while (*end && *end != ' ' && *end != '$')
			end++;
		if (!(res = ft_substr(line, 0, end - line)))
			exit(errno);
		while (*end && *end != ' ')
			end++;
	}
	else
		token_with_dollar_error(line, end, eval);
	return (res);
}

char			*shape_name_fd(char *name, t_eval *eval)
{
	char		*name_fd;

	if (*name == '$')
		name_fd = token_with_dollar(name, eval);
	else
		name_fd = return_token(&name, eval);
//	else if (*curr == ';' || *curr == '|')
//	{
//		while (*curr && *curr == symb && *curr != ' ')
//			curr++;
//		if (!(name_fd = ft_substr((*line), 0, curr - *(line))))
//			exit(errno);
//		(*line) = curr;
//	}
	return (name_fd);
}
