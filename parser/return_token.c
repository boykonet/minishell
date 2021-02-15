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

#include "other.h"
#include "parser.h"
#include "minishell.h"
#include "lexic.h"

char 		*token_without_quotes(char **line, t_eval *eval, const int *spec_char)
{
	char 	*curr;

	curr = NULL;
	if (*(*line) == '$' && !(*spec_char))
		curr = expand_env_arg(line, eval);
	else if ((!ft_strncmp(*line, "~", 2) || !ft_strncmp(*line, "~ ", 2)) && !(*spec_char))
	{
		if (!(curr = ft_strdup(find_data_in_env(eval->env, "HOME", 0))))
			exit(errno);
		(*line)++;
	}
	else
	{
		if (!(curr = ft_calloc(2, sizeof(char))))
			exit(errno);
		if (*(*line) == '\\' && !(*spec_char))
			(*line)++;
		curr[0] = *(*line)++;
	}
	return (curr);
}

char 		*check_line(char **line, t_eval *eval)
{
	char	*curr;
	int 	spec_char;

	spec_char = 0;
	curr = NULL;
	if (*(*line) == '\\')
	{
		(*line)++;
		spec_char = 1;
	}
	if ((*(*line) == '\'' || *(*line) == '\"') && !spec_char)
	{
		curr = handling_tokens_with_quotes(line, eval);
		eval->quotes = 1;
	}
	else
		curr = token_without_quotes(line, eval, &spec_char);
	return (curr);
}

char 		*return_token(char **line, t_eval *eval)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;

	eval->quotes = 0;
	eval->dollar_flag = 0;
	res = NULL;
	if (*(*line))
	{
		if (!(res = ft_strdup("")))
			exit(errno);
		while (*(*line))
		{
			if (spec_symb(eval->quotes, 0, *(*line)))
				break;
			tmp = res;
			if (!(curr = check_line(line, eval))) {
				free(tmp);
				exit(errno);
			}
			res = ft_strjoin(res, curr);
			free(tmp);
			tmp = NULL;
			free(curr);
			if (!res)
				exit(errno);
		}
	}
	return (res);
}