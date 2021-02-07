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

void			write_token_to_list(char **line, t_list **list, t_parser *p)
{
	char 		*str;

	str = return_token(line, p);
	if (!((*list) = ft_lstnew(str)))
		exit(errno);
}

void			first_elem_list(char **line, t_parser *p, t_params **params)
{
	(*line) = remove_spaces((*line));
	while (p->exit_status != 2 && *(*line) && (*(*line) == '<' || *(*line) == '>'))
		open_and_close_fd(line, p, &(p->params));
	(*line) = remove_spaces((*line));
	write_token_to_list(line, &(*params)->args, p);
	if (!p->quotes && !check_unexpected_token((char**)&((*params)->args)->content))
	{
		ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(p->params->args->content, 2);
		ft_putendl_fd("'", 2);
		p->status = 258;
		p->exit_status = 2;
	}
}

int				parsing(char **line, t_parser *p, t_params **params)
{
	t_list		*lst;

	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		first_elem_list(line, p, params);
		lst = (*params)->args;
		while (p->exit_status != 2 && *(*line) && (*(*line) != '|' && *(*line) != ';'))
		{
			(*line) = remove_spaces((*line));
			if (*(*line) && (*(*line) == '<' || *(*line) == '>'))
				open_and_close_fd(line, p, params);
			else if (*(*line) && *(*line) != '|' && *(*line) != ';')
			{
				(*line) = remove_spaces((*line));
				write_token_to_list(line, &lst->next, p);
				lst = lst->next;
			}
		}
	}
	return (0);
}

void			check_pipes_semicolon(char **line, t_parser *p)
{
	(*line) = remove_spaces((*line));
	if (!ft_strncmp((*line), "||", 2))
	{
		ft_putendl_fd("-minishell: syntax error near unexpected token `||'", 2);
		p->exit_status = 2;
		p->status = 258;
	}
	else if (!ft_strncmp((*line), ";;", 2))
	{
		ft_putendl_fd("-minishell: syntax error near unexpected token `;;'", 2);
		p->exit_status = 2;
		p->status = 258;
	}
	else if (*(*line) == '|')
		(*line)++;
}

void			parser(char **line, t_d **data, int *status)
{
	t_parser	p;

	p.env = (*data)->env;
	p.status = *status;
	p.exit_status = (*data)->exit_status == 2 ? 1 : 0;
	p.quotes = 0;
	if (*(*line))
	{
		(*data)->params = new_params_element();
		p.params = (*data)->params;
		parsing(line, &p, &(p.params));
		if (p.exit_status != 2)
			check_pipes_semicolon(line, &p);
		while (p.exit_status != 2 && *(*line) && *(*line) != ';')
		{
			p.params->next = new_params_element();
			parsing(line, &p, &(p.params->next));
			if (p.exit_status == 2)
				break ;
			check_pipes_semicolon(line, &p);
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