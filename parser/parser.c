/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:13:55 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/18 23:13:55 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"
#include "lexic.h"

static char		*simple_token(char **line)
{
	char		*res;
	char		*curr;
	char		c;

	curr = *line;
	c = *(*line);
	if (c == '<' || c == '>')
	{
		while (*(*line) && c == *(*line))
			(*line)++;
	}
	else
		lexic_token(line, 0);
	res = ft_substr(curr, 0, *line - curr);
	if (!res)
		exit(errno);
	return (res);
}

static t_list	*write_token_to_list(char **line)
{
	t_list		*list;
	char		*str;

	str = simple_token(line);
	if (ft_strcmp(str, ""))
	{
		if (!(list = ft_lstnew(str)))
			exit(errno);
		return (list);
	}
	free(str);
	return (NULL);
}

static t_list	*elem_list(char **line, int *pipe_semic)
{
	t_list		*list;

	list = NULL;
	(*line) = remove_spaces((*line));
	if (*(*line))
		list = write_token_to_list(line);
	if (*(*line) == '|')
		*pipe_semic = 1;
	else if (*(*line) == ';')
		*pipe_semic = 2;
	return (list);
}

static t_list	*new_lists(char **line, int *pipe_semic)
{
	t_list		*head;
	t_list		*list;

	head = elem_list(line, pipe_semic);
	list = head;
	while (*(*line) && !(*pipe_semic))
	{
		list->next = elem_list(line, pipe_semic);
		if (list->next)
			list = list->next;
	}
	if (*(*line) == ';' || *(*line) == '|')
		(*line)++;
	return (head);
}

t_params		*parser(char *line)
{
	t_params	*head;
	t_params	*elem;
	int			pipe_semic;

	pipe_semic = 0;
	head = new_params_element();
	elem = head;
	elem->args = new_lists(&line, &pipe_semic);
	elem->pipe_semic = pipe_semic;
	while (*line)
	{
		pipe_semic = 0;
		elem->next = new_params_element();
		elem->next->args = new_lists(&line, &pipe_semic);
		elem->next->pipe_semic = pipe_semic;
		elem = elem->next;
	}
	return (head);
}
