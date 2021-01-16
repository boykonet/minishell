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

int 			check_unexpected_token(char *name_fd)
{
	char 		*err[] = {">>", "<<", "((", "))", ";;", "<", ">", "(", ")", ";"};
	int 		i;

	i = 0;
	while (err[i])
	{
		if (!ft_strncmp(err[i], name_fd, ft_strlen(name_fd)))
			return (0);
		i++;
	}
	return (1);
}

int 			open_fd(char **line, t_env *env, int *fd, int *status)
{
	char 		*redir;
	char 		*curr;
	char 		*name_fd;
	char 		symb;

	(*line) = remove_spaces((*line));
	curr = (*line);
	symb = *(*line);
	while (*curr && *curr == symb && *curr != ' ')
		curr++;
	redir = ft_substr((*line), 0, curr - (*line));
	(*line) = curr;
	(*line) = remove_spaces((*line));
	curr = (*line);
	name_fd = return_token(line, env, status);
//	name_fd = ft_substr((*line), 0, curr - (*line));
	if (!ft_strncmp(name_fd, "", ft_strlen(name_fd)) || check_unexpected_token(name_fd))
		*status = error_handling(NULL, "newline", "syntax error near unexpected token", 2);
	else
	{
		if ((*fd = add_fd(name_fd, redir)) < 0)
			*status = error_handling(NULL, NULL, strerror(errno), 1);
	}
	(*line) = curr;
	free(redir);
	free(name_fd);
	if (status == 0)
		return (1);
	return (0);
}

int 			redir(char **line, t_env *env, int *fd, int *status)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
			return (0);
	}
	if (!(open_fd(line, env, fd, status)))
		return (0);
	return (1);
}