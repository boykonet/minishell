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
		return (0);
	}
	return (1);
}

int 			open_fd(char **line, int *fd, int *status)
{
	char 		*redir;
	char 		*curr;
	char 		*name_fd;
	char 		symb;

	(*line) = remove_spaces((*line));
	curr = (*line);
	symb = *(*line);
	while (*curr && *curr == symb && *curr != ' ')
	{
		curr++;
	redir = ft_substr((*line), 0, curr - (*line));
	(*line) = curr;
	(*line) = remove_spaces((*line));
	curr = (*line);
	while (*curr && *curr != ' ')
		curr++;
	name_fd = ft_substr((*line), 0, curr - (*line));
	if (!ft_strncmp(name_fd, "", ft_strlen(name_fd)))
	{
		*status = error_handling(NULL, "newline", "syntax error near unexpected token", 258);
	}
	else if ()
	{

	}
	else
	{
		if ((*fd = add_fd(name_fd, redir)) < 0)
			*status = error_handling(NULL, NULL, strerror(errno), 1);
	}
	(*line) = curr;
	free(redir);
	free(name_fd);
	return (1);
}

int 			redir(char **line, int *fd, int *status)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
			return (0);
	}
	if (!(open_fd(line, fd)))
		return (0);
	return (1);
}