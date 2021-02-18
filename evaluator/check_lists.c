/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 02:20:31 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 02:20:31 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "evaluator.h"
#include "lexic.h"

static t_list		*list_dollar(char **line, t_eval *eval)
{
	t_list			*list;
	char			*token;

	list = NULL;
	*line = remove_spaces(*line);
	token = *line;
	if (*(*line))
	{
		if (spec_symb(eval->quotes, 0, 0, *(*line)) > 1)
		{
			lexic_token(line, 2);
			token = ft_substr(token, 0, *line - token);
		}
		else
			token = return_token(line, eval);
		if (token)
		{
			if (!(list = ft_lstnew(token)))
				exit(errno);
		}
	}
	return (list);
}

static t_list		*dollar_tokens(char *line, t_eval *eval)
{
	t_list			*head;
	t_list			*list;

	list = NULL;
	if ((head = list_dollar(&line, eval)))
		list = head;
	while (*line)
	{
		if ((list->next = list_dollar(&line, eval)))
			list = list->next;
	}
	return (head);
}

static void			check_redir(t_list **list, t_eval *eval, t_params **params)
{
	t_list			*redir;
	t_list			*name;
	t_list			*next;

	redir = (*list);
	name = (*list)->next;
	next = (*list)->next->next;
	open_and_close_fd(redir->content, name->content, eval, params);
	if (!eval->exit_status)
	{
		lst_delete(&(*params)->args, redir);
		lst_delete(&(*params)->args, name);
	}
	*list = next;
}

static void			check_eval_token(t_list **list, t_eval *eval, \
					t_params **params)
{
	t_list			*next;
	t_list			*tokens;
	char			*tmp;
	char			*tmp2;

	tmp = (char*)(*list)->content;
	next = (*list)->next;
	tmp2 = tmp;
	(*list)->content = return_token(&tmp2, eval);
	if ((*list)->content)
	{
		if (!ft_strcmp((*list)->content, "") && !eval->quotes)
			lst_delete(&(*params)->args, *list);
		else if (ft_strchr((*list)->content, ' ') && !eval->quotes && \
		eval->dollar_flag == 1)
		{
			tokens = dollar_tokens((*list)->content, eval);
			lst_replase(&(*params)->args, &tokens, *list);
		}
	}
	free(tmp);
	*list = next;
}

void				check_lists(t_params *params, t_eval *eval)
{
	t_list			*list;

	list = params->args;
	while (list && eval->exit_status != 2)
	{
		if (!ft_strcmp(list->content, ">>") || \
		!ft_strcmp(list->content, ">") || \
		!ft_strcmp(list->content, "<"))
			check_redir(&list, eval, &params);
		else
			check_eval_token(&list, eval, &params);
	}
}
