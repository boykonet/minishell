/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_tokens_with_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:30:35 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/18 22:30:35 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "other.h"
#include "parser.h"
#include "minishell.h"

char		*tokens_with_single_quotes(char **line)
{
	char 	*token;
	char 	*curr;

	curr = (*line);
	curr++;
	while (*curr)
	{
		if (*curr == '\'')
			break ;
		curr++;
	}
	token = ft_substr((*line), 1, curr - (*line) - 1);
	(*line) = ++curr;
	if (!token)
		exit(errno);
	return (token);
}

int 		validate_token_with_double_quotes(char **line, int *spec_char)
{
	*spec_char = 0;
	if (*(*line) == '\\')
	{
		if (*(*line + 1) == '\"' || *(*line + 1) == '$' || *(*line + 1) == '\\')
		{
			(*line)++;
			*spec_char = 1;
		}
		else if (*(*line + 1) == '!')
			*spec_char = 1;
	}
	if (*(*line) == '\"' && !*spec_char)
	{
		(*line)++;
		return (0);
	}
	return (1);
}

char		*tokens_with_double_quotes(char **line, t_env *env, int *status)
{
	char 	*token;
	char	*tmp;
	char 	*curr;
	int 	spec_char;

	if (!(token = ft_strdup("")))
		exit(errno);
	(*line)++;
	while (*(*line))
	{
		tmp = token;
		if (!validate_token_with_double_quotes(line, &spec_char))
			break ;
		if (*(*line) == '$' && !spec_char)
		{
			curr = expand_env_arg(line, env, status);
			token = ft_strjoin(token, curr);
			free(curr);
			if (!token)
				exit(errno);
		}
		else
			token = append_to_array(token, *(*line)++);
		free(tmp);
	}
	return (token);
}

char		*handling_tokens_with_quotes(char **line, t_env *env, int *status)
{
	char 	*res;

	res = NULL;
	if (*(*line) == '\'')
		res = tokens_with_single_quotes(line);
	else if (*(*line) == '\"')
		res = tokens_with_double_quotes(line, env, status);
	return (res);
}
