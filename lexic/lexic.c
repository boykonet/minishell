/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 02:54:56 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 02:54:56 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "lexic.h"

static int		check_redir_fd(char **line)
{
	char		*nfd;
	char		*curr;
	int			status;

	status = 0;
	if (!ft_strncmp(*line, ">>", 2))
		*line = *line + 2;
	else if (!ft_strncmp(*line, ">", 1) || !ft_strncmp(*line, "<", 1))
		*line = *line + 1;
	*line = remove_spaces(*line);
	curr = (*line);
	lexic_token(line, 2);
	nfd = ft_substr(curr, 0, *line - curr);
	if (spec_symb(0, 0, 0, *nfd) > 0)
		status = check_unexpected_token(nfd);
	free(nfd);
	return (status);
}

static int		check_semic_pipes(char **line)
{
	int			status;

	status = 0;
	if ((*(*line + 1) == ' ' || *(*line) == ';') && (*(*line) != *(*line + 1)))
		(*line)++;
	*line = remove_spaces(*line);
	if (*(*line) != '>' && *(*line) != '<' && *(*line) != '\0')
		status = check_unexpected_token(*line);
	return (status);
}

int				lexic(char *line)
{
	int			r;
	int			status;
	int			count_tokens;

	status = 0;
	count_tokens = 0;
	while (*line && !status)
	{
		line = remove_spaces(line);
		r = lexic_token(&line, 0);
		if (r == 1)
			count_tokens++;
		if (r == 2)
		{
			status = check_semic_pipes(&line);
			count_tokens = 0;
		}
		else if (r == 3)
			status = check_redir_fd(&line);
		else if (r == 4)
			status = check_unexpected_token(line);
	}
	return (status);
}
