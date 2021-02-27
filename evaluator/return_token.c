/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:28:40 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/18 22:28:40 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "evaluator.h"
#include "minishell.h"
#include "lexic.h"

static char		*home_token(t_eval *eval)
{
	char		*curr;

	if ((curr = find_data_in_env(eval->env, "HOME", 0)))
		curr = ft_strdup(curr);
	else
		curr = ft_strdup(eval->home);
	if (!curr)
		exit(errno);
	return (curr);
}

static char		*token_without_quotes(char **line, t_eval *eval, \
				const int *spec_char)
{
	char		*curr;

	curr = NULL;
	if (*(*line) == '$' && !(*spec_char))
		curr = expand_env_arg(line, eval);
	else if (*(*line) == '~' && !(*spec_char))
	{
		curr = home_token(eval);
		(*line)++;
	}
	else
	{
		if (!(curr = ft_calloc(2, sizeof(char))))
			exit(errno);
		if (*(*line) == '\\' && !(*spec_char))
			(*line)++;
		curr[0] = *(*line);
		if (*(*line))
			(*line)++;
	}
	return (curr);
}

static char		*check_line(char **line, t_eval *eval, int *esc)
{
	char		*curr;

	curr = NULL;
	if (*esc > 0)
		*esc = 0;
	if (*(*line) == '\\')
	{
		(*line)++;
		*esc = 1;
	}
	if ((*(*line) == '\'' || *(*line) == '\"') && !(*esc))
		curr = handling_tokens_with_quotes(line, eval);
	else
		curr = token_without_quotes(line, eval, esc);
	return (curr);
}

static void		token_res(char **line, t_eval *eval, char **res)
{
	char		*curr;
	char		*tmp;
	int			escaping;

	escaping = 0;
	while (*(*line))
	{
		if (spec_symb(eval->quotes, escaping, 0, *(*line)))
			break ;
		tmp = *res;
		if (!(curr = check_line(line, eval, &escaping)))
		{
			free(tmp);
			exit(errno);
		}
		*res = ft_strjoin(*res, curr);
		free(tmp);
		tmp = NULL;
		free(curr);
		if (!(*res))
			exit(errno);
	}
}

char			*return_token(char **line, t_eval *eval)
{
	char		*res;

	eval->quotes = 0;
	eval->dollar_flag = 0;
	res = NULL;
	if (*(*line))
	{
		if (!(res = ft_strdup("")))
			exit(errno);
		token_res(line, eval, &res);
	}
	return (res);
}
