/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:11:07 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/21 00:11:07 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int			ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || ft_isalpha(c))
		return (1);
	return (0);
}

int			check_tokens(char c)
{
	return (c != '|' && c != ';')
}

int			parser(t_params *params, char **line)
{
	char	buff[2];
	char	*tmp;
	int		count_args;

	i = 0;
	count_args = 0;
	buff[1] = '\0';
	while (*line)
	{
		while (ft_isalpha(*line) && check_tokens(*line))
		{
			if (!params->command)
				params->command = ft_strdup("");
			buff[0] = *line;
			tmp = params->command;
			params->command = ft_strjoin(params->command, buff);
			free(tmp);
			tmp = NULL;
			line++;
		}
		else if (*line == '-')
		{
			line++;
			if (!params->flags)
				params->flags = ft_strdup("");
			while (ft_isalpha(*line) && check_tokens(*line))
			{
				buff[0] = *line;
				tmp = params->flags;
				params->flags = ft_strjoin(params->flags, buff);
				free(tmp);
				tmp = NULL;
				line++;
			}
			if (!check_tokens(*line))
				return (-1);
		}
		else if (*line == '$')
		{
			while (ft_isalnum(*line) || *line == '=' || *line == '$')
			{
				buff[0] = *line;
				tmp = params->args[count_args];
				params->args[count_args] = ft_strjoin(params->args[count_args], buff);
				free(tmp);
				tmp = NULL;
				line++;
			}
			count_args++;
		}
		line++;
	}
	if (*line == '|')
		return (2);
	else if (*line == ';')
		return (1);
	return (0);
}
