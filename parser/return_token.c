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

char 		*token_without_quotes(char **line, t_parser *p, const int *spec_char)
{
	char 	*curr;

	curr = NULL;
	if (*(*line) == '$' && !(*spec_char))
		curr = expand_env_arg(line, p);
	else if ((!ft_strncmp(*line, "~", 2) || !ft_strncmp(*line, "~ ", 2)) && !(*spec_char))
	{
		if (!(curr = ft_strdup(find_data_in_env(p->env, "HOME", 0))))
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

char 		*check_line(char **line, t_parser *p)
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
		curr = handling_tokens_with_quotes(line, p);
		p->quotes = 1;
	}
	else
		curr = token_without_quotes(line, p, &spec_char);
	return (curr);
}

char 		*return_token(char **line, t_parser *p)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;
	char 	c;

	p->quotes = 0;
	p->dollar_flag = 0;
	tmp = NULL;
	if (!(res = ft_strdup("")))
		exit(errno);
	c = *(*line);
	while (c && c != ' ' && c != ';' && c != '|' && c != '>' && c != '<' && c != ')' && c != '(' && c != '&')
	{
		tmp = res;
		if (!(curr = check_line(line, p)))
		{
			free(tmp);
			exit(errno);
		}
		res = ft_strjoin(res, curr);
		free(tmp);
		tmp = NULL;
		free(curr);
		if (!res)
			exit(errno);
		c = *(*line);
	}
	free(tmp);
	return (res);
}