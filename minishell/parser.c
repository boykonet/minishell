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

int 			copying_redir_fd(t_list **curr, char **name_redir, char **name_fd, int *fd_name)
{
	if (!((*name_redir) = ft_strdup((*curr)->content)))
		return (0);
	if ((*curr)->next)
	{
		if (!((*name_fd) = ft_strdup((*curr)->next->content)))
			return (0);
	}
	*fd_name = add_fd(*name_fd, *name_redir);
	(*curr) = (*curr)->next->next;
	return (1);
}

int 			redirects(char *redir)
{
	if (!ft_strncmp(redir, "<", ft_strlen(redir)))
		return (0);
	else if (!ft_strncmp(redir, ">", ft_strlen(redir)) || \
				!ft_strncmp(redir, ">>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "1>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "1>>", ft_strlen(redir)))
		return (1);
	else if (!ft_strncmp(redir, "2>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "2>>", ft_strlen(redir)))
		return (2);
	return (-1);
}

int 			check_redir(t_list **curr, t_params *params, t_fd *fd)
{
	char 			*redir;
	unsigned char	*meta;

	redir = NULL;
	meta = 0;
	redir = (*curr)->content;
	if (!redirects(redir))
	{
		if (fd->redir_in)
		{
			free(fd->redir_in);
			fd->redir_in = NULL;
		}
		if (fd->name_in)
		{
			free(fd->name_in);
			fd->name_in = NULL;
		}
		if (fd->in > 2)
			close(fd->in);
		if (!(copying_redir_fd(curr, &fd->redir_in, &fd->name_in, &fd->in)))
			return (0);
	}
	else if (redirects(redir) == 1)
	{
		if (fd->redir_out)
		{
			free(fd->redir_out);
			fd->redir_out = NULL;
		}
		if (fd->name_out)
		{
			free(fd->name_out);
			fd->name_out = NULL;
		}
		if (fd->out > 2)
			close(fd->out);
		if (!(copying_redir_fd(curr, &fd->redir_out, &fd->name_out, &fd->out)))
			return (0);
	}
	else if (redirects(redir) == 2)
	{
		if (fd->redir_err)
		{
			free(fd->redir_err);
			fd->redir_err = NULL;
		}
		if (fd->name_err)
		{
			free(fd->name_err);
			fd->name_err = NULL;
		}
		if (fd->err > 2)
			close(fd->err);
		if (!(copying_redir_fd(curr, &fd->redir_err, &fd->name_err, &fd->err)))
			return (0);
	}
	if (fd->in == -1 || fd->out == -1 || fd->err == -1)
		return (0);
	return (1);
}

void 			*parser(t_list **tokens, t_params *params, t_fd *fd, int *status)
{
	t_list		*curr;
	size_t 		count;

	count = 0;
	if (redirects((*tokens)->content) == -1)
	{
		if (!(params->cmd = ft_strdup((*tokens)->content)))
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	curr = (*tokens);
	while (curr && ft_strncmp(curr->content, "|", ft_strlen(curr->content)))
	{
		if (redirects(curr->content) > -1)
		{
			if (curr->next)
				curr = curr->next->next;
			else
				curr = curr->next;
			continue ;
		}
		count++;
	}
	if (!(params->args = ft_calloc(count + 1, sizeof(char*))))
		return (NULL);
	params->args[count] = NULL;
	count = 0;
	while ((*tokens) && ft_strncmp((*tokens)->content, "|", ft_strlen((*tokens)->content)))
	{
		if (redirects((*tokens)->content) > -1)
		{
			if (!check_redir(tokens, params, fd))
				return (NULL);
			continue ;
		}
		if (!(params->args[count++] = ft_strdup((*tokens)->content)))
			return (NULL);
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
	return ((*tokens));
}