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

static void 	check_pipes_semic(t_parser *p, char *line)
{
	char 		c;
	char 		*curr;
	char 		*buff;

	line = remove_spaces(line);
	c = *line;
	curr = line;
	buff = NULL;
	while (*curr == c)
		curr++;
	if (!(buff = ft_substr(line, 0, curr - line)))
		exit(errno);
	check_unexpected_token(buff, p);
	free(buff);
}

//char 		*simple_without_quotes(char **line, int escaping)
//{
//	char 	*curr;
//
//	if (!(curr = ft_calloc(2, sizeof(char))))
//		exit(errno);
//	curr[0] = *(*line)++;
//	return (curr);
//}

//char 		*simple_line(char **line, t_parser *p)
//{
//	char	*curr;
//
//	curr = NULL;
//	p->escaping = 0;
//	if (*(*line) == '\\')
//		p->escaping = 1;
//	if ((*(*line) == '\'' || *(*line) == '\"') && !p->escaping)
//		curr = simple_with_quotes(line, p);
//	else
//		curr = simple_without_quotes(line, p->escaping);
//	return (curr);
//}

char 			*simple_token(char **line, t_parser *p)
{
	char 	*res;
	char 	*tmp;
//	char 	*curr;
	char 	c;

	p->quotes = 0;
	p->dollar_flag = 0;
	tmp = NULL;
	if (!(res = ft_strdup("")))
		exit(errno);
	c = *(*line);
	while (c)
	{
		tmp = res;
		if (p->quotes == 0 && (c == ' ' || c == ';' || c == '|' || c == '>' || \
			c == '<' || c == ')' || c == '(' || c == '&'))
			break ;
		if (c == '\\' && p->escaping == 0)
			p->escaping = 1;
		else if (c == '\\' && p->escaping == 1)
			p->escaping = 2;
		if ((c == '\'' || c == '\"') && p->escaping == 0 && p->quotes == 0)
			p->quotes = 1;
		if ((c == '\'' || c == '\"') && p->escaping == 0 && p->quotes == 1)
			p->quotes = 2;
		if (p->escaping == 1 && c != '\\' || p->escaping == 2)
			p->escaping = 0;
		if (p->quotes == 2)
			p->quotes = 0;
		res = append_to_array(res, *(*line)++);
		free(tmp);
		tmp = NULL;
		if (!res)
			exit(errno);
		c = *(*line);
	}
	free(tmp);
	return (res);
}

void			write_token_to_list(char **line, t_list **list, t_parser *p, t_params **params)
{
	char 		*str;
//	char 		*token;
//	char 		*tmp;

	str = simple_token(line, p);
	(*list) = ft_lstnew(str);
	if (!(*list))
		exit(errno);
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
//	free(str);
	(*line) = remove_spaces((*line));
	if (*(*line) == ';' || *(*line) == '|')
	{
		if (*(*line) == '|')
			(*params)->pipe_semic = 1;
		else if (*(*line) == ';')
			(*params)->pipe_semic = 2;
	}
//	if (*(*line) == ';' || *(*line) == '|' || *(*line) == '&' || *(*line) == ')' || *(*line) == '(')
//		p->symb = 1;
//	if (p->symb && !(*params)->args)
//	if (p->symb && (*(*line) == *(*line + 1) || !*(*line + 1)) && !(*params)->args)
//		check_pipes_semic(p, *line);
//	else if (p->symb && *(*line) != *(*line + 1))
//		check_pipes_semic(p, (*line) + 1);
}

void			elem_list(char **line, t_parser *p, t_params **params, t_list **lst)
{
	(*line) = remove_spaces((*line));
	while (p->exit_status != 2 && *(*line) && (*(*line) == '<' || *(*line) == '>'))
		open_and_close_fd(line, p, params);
	(*line) = remove_spaces((*line));
	if (p->exit_status != 2 && *(*line))
		write_token_to_list(line, lst, p, params);
}

void			new_lists(char **line, t_parser *p, t_params **params)
{
	t_list		*lst;

	lst = NULL;
	if (*(*line))
	{
		while (p->exit_status != 2 && !lst && *(*line))
			elem_list(line, p, params, &lst);
		(*params)->args = lst;
		while (p->exit_status != 2 && *(*line))
		{
			elem_list(line, p, params, &lst->next);
			if (lst->next)
				lst = lst->next;
		}
	}
	if (p->exit_status != 2 && (*(*line) == ';' || *(*line) == '|'))
		(*line)++;
}

void 			init_parser(t_d **data, t_parser *p, const int *status)
{
	p->copy_line = &(*data)->line;
	p->env = (*data)->env;
	p->status = *status;
	p->exit_status = (*data)->exit_status == 2 ? 1 : 0;
	p->quotes = 0;
	p->dollar_flag = 0;
	p->pipe_semic = 0;
	p->escaping = 0;
}

void			parser(char *line, t_d **data, int *status)
{
	t_parser	p;

	init_parser(data, &p, status);
	while (*line)
	{
		(*data)->params = new_params_element();
		p.params = (*data)->params;
		new_lists(&line, &p, &p.params);
		if (p.exit_status == 2)
			break ;
		if (!ft_lstsize(p.params->args))
		{
			params_free(&(*data)->params, del_params_content);
			(*data)->params = NULL;
		}
		if ((*data)->params)
			break ;
	}
	while (p.params->pipe_semic != 2 && p.exit_status != 2 && *line)
	{
		p.params->next = new_params_element();
		new_lists(&line, &p, &(p.params->next));
		if (!ft_lstsize(p.params->args))
		{
			params_free(&p.params, del_params_content);
			p.params = NULL;
		}
		else
		{
			if (p.exit_status == 2)
				break ;
			p.params = p.params->next;
		}
	}
	if (p.status > 0 && p.exit_status == 1)
	{
		p.status = 0;
		p.exit_status = 0;
	}
	*status = p.status;
	(*data)->exit_status = p.exit_status;
}