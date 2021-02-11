/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:13:02 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/24 18:13:02 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"
#include "parser.h"
#include "minishell.h"

int				redirect_and_name_fd(char **line, t_parser *p, int *fd)
{
	char		*redir;
	char		*curr;
	char		*nfd;

	curr = (*line);
	while (*curr && *curr == *(*line) && *curr != ' ')
		curr++;
	if (!(redir = ft_substr((*line), 0, curr - (*line))))
		exit(errno);
	curr = remove_spaces(curr);
	(*line) = curr;
	nfd = shape_name_fd(line, curr, p);
	if (!p->quotes)
		check_unexpected_token(nfd, p);
	if (p->exit_status != 2)
	{
		if ((*fd = open_fd(nfd, redir)) < 0)
		{
			p->status = 1;
			p->exit_status = 2;
		}
	}
	free(redir);
	free(nfd);
	if (p->status && p->exit_status == 2)
		return (0);
	return (1);
}

static int		reopen_fd(char **line, t_parser *p, int *fd)
{
	if (*fd > 2)
		close_fd(*fd);
	if (!redirect_and_name_fd(line, p, fd))
		return (0);
	return (1);
}

int				open_and_close_fd(char **line, t_parser *p, t_params **params)
{
	int			res;

	res = 1;
	if (check_redir(line) == 0)
		res = reopen_fd(line, p, &((*params)->in));
	else if (check_redir(line) == 1)
		res = reopen_fd(line, p, &((*params)->out));
	else if (check_redir(line) == 2)
		res = reopen_fd(line, p, &((*params)->err));
	return (res);
}
