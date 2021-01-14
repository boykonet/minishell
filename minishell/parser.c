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

int 			open_fd(char **line, int *fd)
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
	while (*curr && *curr != ' ')
		curr++;
	name_fd = ft_substr((*line), 0, curr - (*line));
	*fd = add_fd(name_fd, redir);
	(*line) = curr;
	free(redir);
	free(name_fd);
	return (1);
}

int 			redir(char **line, int *fd)
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
//
//void 			*parser(t_list **tokens, t_params *params, t_fd *fd, int *status)
//{
//	t_list		*curr;
//	size_t 		count;
//
//	count = 0;
//	if (redirects((*tokens)->content) == -1)
//	{
//		if (!(params->cmd = ft_strdup((*tokens)->content)))
//			return (NULL);
//		(*tokens) = (*tokens)->next;
//	}
//	curr = (*tokens);
//	while (curr && ft_strncmp(curr->content, "|", ft_strlen(curr->content)))
//	{
//		if (redirects(curr->content) > -1)
//		{
//			if (curr->next)
//				curr = curr->next->next;
//			else
//				curr = curr->next;
//			continue ;
//		}
//		curr = curr->next;
//		count++;
//	}
//	if (!(params->args = ft_calloc(count + 1, sizeof(char*))))
//		return (NULL);
//	params->args[count] = NULL;
//	count = 0;
//	while ((*tokens) && ft_strncmp((*tokens)->content, "|", ft_strlen((*tokens)->content)))
//	{
//		if (redirects((*tokens)->content) > -1)
//		{
//			if (!check_redir(tokens, params, fd))
//				return (NULL);
//			continue ;
//		}
//		if (!(params->args[count++] = ft_strdup((*tokens)->content)))
//			return (NULL);
//		(*tokens) = (*tokens)->next;
//	}
//	return ((*tokens));
//}