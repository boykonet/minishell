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

#include "builtins.h"
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

char 			*shape_name_fd(char **line, char *curr, t_env *env, int *status)
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
		name_fd = return_token(line, env, status);
	return (name_fd);
}

int				redirect_and_name_fd(char **line, t_env *env, int *fd, \
									int *status)
{
	char 		*redir;
	char 		*curr;
	char 		*nfd;
	int 		flag;

	curr = (*line);
	flag = 1;
	while (*curr && *curr == *(*line) && *curr != ' ')
		curr++;
	if (!(redir = ft_substr((*line), 0, curr - (*line))))
		exit(errno);
	curr = remove_spaces(curr);
	(*line) = curr;
	nfd = shape_name_fd(line, curr, env, status);
	if (!check_unexpected_token(&nfd))
	{
		ft_printf("-minishell: syntax error near unexpected token `%s'\n", nfd);
		*status = 258;
		flag = 0;
	}
	else
	{
		if ((*fd = open_fd(nfd, redir)) < 0)
		{
			ft_printf("-minishell: %s: %s\n", nfd, strerror(errno));
			*status = 1;
			flag = 0;
		}
	}
	free(redir);
	free(nfd);
	if (*status > 0 && !flag)
		return (0);
	return (1);
}

int				reopen_fd(char **line, t_env *env, int *fd, int *status)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
		{
			ft_printf("-minishell: %s\n", strerror(errno));
			*status = errno;
			return (0);
		}
	}
	if (!redirect_and_name_fd(line, env, fd, status))
		return (0);
	return (1);
}

int 			open_and_close_fd(char **line, t_params **params, \
									t_env *env, int *status)
{
	int 		res;

	res = 1;
	if (check_redir(line) == 0)
		res = reopen_fd(line, env, &((*params)->in), status);
	else if (check_redir(line) == 1)
		res = reopen_fd(line, env, &((*params)->out), status);
	else if (check_redir(line) == 2)
		res = reopen_fd(line, env, &((*params)->err), status);
	return (res);
}
