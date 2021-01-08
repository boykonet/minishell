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

void 			*copying_redir_fd(t_list *curr, char **name_redir, char **name_fd)
{
	if (!name_redir)
	{
		if (!(name_redir = ft_strdup(curr->content)))
			return (NULL);
		if (curr->next && !name_fd)
			if (!(name_fd = ft_strdup(curr->next->content)))
				return (NULL);
		curr = curr->next->next;
	}
	return (curr);
}

int 			check_redir(t_list **curr, t_params *params, t_fd *fd, int flag)
{
	char 			*redir;
	unsigned char	*meta;

	redir = NULL;
	meta = 0;
	if (flag == 0)
	{
		if ((*curr)->next)
			(*curr) = (*curr)->next->next;
	}
	else
	{
		if (redirects(curr))
		{
			redir = (*curr)->content;
			if (!ft_strncmp(redir, "<", ft_strlen(redir)))
			{
				if ()
				(*curr) = copying_redir_fd((*curr), &params->redir_in, &fd->name_in);
			}
			else if (!ft_strncmp(redir, ">", ft_strlen(redir)) || \
					!ft_strncmp(redir, ">>", ft_strlen(redir)) || \
					!ft_strncmp(redir, "1>", ft_strlen(redir)) || \
					!ft_strncmp(redir, "1>>", ft_strlen(redir)))
				(*curr) = copying_redir_fd((*curr), &params->redir_out, &fd->name_out);
			else if (!ft_strncmp(redir, "2>", ft_strlen(redir)) || \
					!ft_strncmp(redir, "2>>", ft_strlen(redir)))
				(*curr) = copying_redir_fd((*curr), &params->redir_err, &fd->name_err);
		}
	}
	return (1);
}

void 			*parser(t_list **tokens, t_params *params, t_fd *fd, int *status)
{
	t_list		*curr;
	size_t 		count;

	count = 0;
	if (!redirects(tokens))
	{
		if (!(params->cmd = ft_strdup((*tokens)->content)))
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	curr = (*tokens);
	while (curr && ft_strncmp(curr->content, "|", ft_strlen(curr->content)))
	{
		if (check_redir())
		{
			count++;
			curr = curr->next;
		}
	}
	if (!(params->args = ft_calloc(count + 1, sizeof(char*))))
		return (NULL);
	params->args[count] = NULL;
	count = 0;
	while ((*tokens) && ft_strncmp((*tokens)->content, "|", ft_strlen((*tokens)->content)))
	{
		params->args[count++] = ft_strdup((*tokens)->content);
		(*tokens) = (*tokens)->next;
	}
	if (!fd->name_in || !fd->name_out || !fd->name_err)
	{
		if (!fd->name_in)
			fd->name_in = ft_strdup("stdin");
		if (!fd->name_out)
			fd->name_out = ft_strdup("stdout");
		if (!fd->name_err)
			fd->name_err = ft_strdup("stderr");
		if (!fd->name_in || !fd->name_out || !fd->name_err)
			return (NULL);
	}
	return (tokens);
}