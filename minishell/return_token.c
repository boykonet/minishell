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

#include "../minishell.h"

char 		*token_without_quotes(char **line, t_env *env, int *spec_char, int *status)
{
	char 	*curr;

	curr = NULL;
	if (*(*line) == '$' && !*spec_char)
		curr = expand_env_arg(line, env, status);
	else
	{
		if (!(curr = ft_calloc(2, sizeof(char))))
			return (NULL);
		if (*(*line) == '\\')
			(*line)++;
		curr[0] = *(*line)++;
	}
	return (curr);
}

char 		*check_line(char **line, t_env *env, int *status)
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
		curr = handling_tokens_with_quotes(line, env, status);
	else
	{
		if (!(curr = token_without_quotes(line, env, &spec_char, status)))
			return (NULL);
	}
	return (curr);
}

char 		*return_token(char **line, t_env *env, int *status)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;

	if (!(res = ft_strdup("")))
		exit(errno);
	while (*(*line) && *(*line) != ' ' && *(*line) != ';')
	{
		tmp = res;
		if (!(curr = check_line(line, env, status)))
		{
			free(tmp);
			exit(errno);
		}
		res = ft_strjoin(res, curr);
		free(tmp);
		free(curr);
		if (!res)
			exit(errno);
	}
	return (res);
}
