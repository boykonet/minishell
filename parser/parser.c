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

#include "other.h"
#include "parser.h"
#include "minishell.h"
#include "lexic.h"

//	(*line) = remove_spaces((*line));
//	while (p->exit_status != 2 && *(*line) && (*(*line) == '<' || *(*line) == '>'))
//		open_and_close_fd(line, p, params);


//	if (ft_strchr(str, ' ') && p->dollar_flag == 1 && !p->quotes)
//	{
//		tmp = *p->copy_line;
//		*p->copy_line = ft_strjoin(str, (*line));
//		free(tmp);
//		free(str);
//		str = NULL;
//		if (!(*p->copy_line))
//			exit(errno);
//		(*line) = *p->copy_line;
//	}
//	else if (((p->quotes && !ft_strncmp(str, "", 1)) || ft_strncmp(str, "", 1)) || p->dollar_flag == 2)
//	{
//		if (!(token = ft_strdup(str)))
//			exit(errno);
//		(*list) = ft_lstnew(token);
//		free(str);
//	}


//	if (*(*line))
//	{
//		while (!p->pipe_semic && !lst && *(*line))
//			elem_list(line, p, params, &lst);
//		elem_list(line, p, params, &lst);
//		(*params)->args = lst;
//		while (!p->pipe_semic && *(*line))
//		{
//			elem_list(line, p, params, &lst->next);
//			if (lst->next)
//				lst = lst->next;
//		}
//	}


//		if (!ft_lstsize(p.params->args))
//		{
//			params_free(&p.params, del_params_content);
//			p.params = NULL;
//		}
//		else
//			p.params = p.params->next;



char 			*simple_token(char **line)
{
	char 	*res;
	char 	*curr;

	curr = *line;
	lexic_token(line, 1);
	res = ft_substr(curr, 0, *line - curr);
	if (!res)
		exit(errno);
	return (res);
}

t_list 			*write_token_to_list(char **line)
{
	t_list 		*list;
	char 		*str;

	str = simple_token(line);
	list = NULL;
	if (ft_strcmp(str, ""))
	{
		if (!(list = ft_lstnew(str)))
			exit(errno);
		return (list);
	}
	free(str);
	return (NULL);
}

t_list			*elem_list(char **line, int *pipe_semic)
{
	t_list 		*list;

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

t_list 			*new_lists(char **line, int *pipe_semic)
{
	t_list 		*head;
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

t_params 		*parser(char *line)
{
	t_params	*head;
	t_params	*elem;
	int 		pipe_semic;

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