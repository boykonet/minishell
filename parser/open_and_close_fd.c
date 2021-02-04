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

int 			check_unexpected_token(char **name_fd)
{
	char 		*err[] = {">>", "<<", ";;", "||", "<", ">", "(", ")", ";", \
							"|", "", NULL};
	char 		*tmp;
	int 		i;

	i = 0;
	tmp = *name_fd;
	while (err[i])
	{
		if (**name_fd == *err[i] && \
		!ft_strncmp(err[i], *name_fd, ft_strlen(err[i])) && \
		!ft_isalpha(*(*name_fd + ft_strlen(err[i]))))
		{
			if (!ft_strncmp(*name_fd, "", ft_strlen(*name_fd)))
				*name_fd = ft_strdup("newline");
			else
				*name_fd = ft_strdup(err[i]);
			free(tmp);
			if (!*name_fd)
				exit(errno);
			return (0);
		}
		i++;
	}
	return (1);
}

char 			*shape_name_fd(char **line, char *curr, t_parser *p)
{
	char 		symb;
	char 		*name_fd;

	symb = *(*line);
	if (*curr == ';' || *curr == '|')
	{
		while (*curr && *curr == symb && *curr != ' ')
			curr++;
		if (!(name_fd = ft_substr((*line), 0, curr - *(line))))
			exit(errno);
		(*line) = curr;
	}
	else
		name_fd = return_token(line, p);
	return (name_fd);
}

int				redirect_and_name_fd(char **line, t_parser *p, int *fd)
{
	char 		*redir;
	char 		*curr;
	char 		*nfd;

	curr = (*line);
	while (*curr && *curr == *(*line) && *curr != ' ')
		curr++;
	if (!(redir = ft_substr((*line), 0, curr - (*line))))
		exit(errno);
	curr = remove_spaces(curr);
	(*line) = curr;
	nfd = shape_name_fd(line, curr, p);
	if (!check_unexpected_token(&nfd))
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(nfd, 2);
		ft_putendl_fd("'", 2);
		p->status = 258;
		p->exit_status = 2;
	}
	else
	{
		if ((*fd = open_fd(nfd, redir)) < 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putstr_fd(nfd, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			p->status = 1;
			p->exit_status = 2;
		}
	}
	free(redir);
	free(nfd);
	if (p->status && p->exit_status)
		return (0);
	return (1);
}

int				reopen_fd(char **line, t_parser *p, int *fd)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			p->status = errno;
			p->exit_status = 2;
			return (0);
		}
	}
	if (!redirect_and_name_fd(line, p, fd))
		return (0);
	return (1);
}

int 			open_and_close_fd(char **line, t_parser *p, t_params **params)
{
	int 		res;

	res = 1;
	if (check_redir(line) == 0)
		res = reopen_fd(line, p, &((*params)->in));
	else if (check_redir(line) == 1)
		res = reopen_fd(line, p, &((*params)->out));
	else if (check_redir(line) == 2)
		res = reopen_fd(line, p, &((*params)->err));
	return (res);
}
