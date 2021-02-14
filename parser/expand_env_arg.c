/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:09:47 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/24 17:09:47 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "other.h"
#include "parser.h"
#include "minishell.h"

char		*find_and_write_env(char **line, t_env *env)
{
	char	*res;
	char	*curr;
	char	*arg;

	(*line)++;
	curr = (*line);
	while (*curr && (ft_isalnum(*curr) || *curr == '_'))
		curr++;
	if (!(arg = ft_substr((*line), 0, curr - (*line))))
		exit(errno);
	res = find_data_in_env(env, arg, 0);
	if (!res)
		res = ft_strdup("");
	else
		res = ft_strdup(res);
	free(arg);
	(*line) = curr;
	if (!res)
		exit(errno);
	return (res);
}

char		*expand_env_arg(char **line, t_eval *eval)
{
	char	*res;

	res = NULL;
	eval->dollar_flag = 1;
	if (!ft_strncmp(*line, "$?", 2))
	{
		res = ft_itoa(eval->status);
		(*line) = *(line) + 2;
		if (!res)
			exit(errno);
		eval->dollar_flag = 2;
	}
	else if (*(*line) == '$' && (!ft_isalnum(*(*line + 1)) || \
				*(*line + 1) == '\\'))
	{
		if (!(res = ft_strdup("$")))
			exit(errno);
		(*line)++;
	}
	else
		res = find_and_write_env(line, eval->env);
	return (res);
}
