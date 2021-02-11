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
	char 		*tmp;

	str = return_token(line, p);
	(*line) = remove_spaces((*line));
	if (ft_strncmp((*line), "", 1) && *(*line) == *(*line + 1))
		if (!check_unexpected_token((*line), p))
			return ;
	if (ft_strchr(str, ' ') && p->dollar_flag == 1 && !p->quotes)
	{
		tmp = *p->copy_line;
		*p->copy_line = ft_strjoin(str, (*line));
		free(tmp);
		free(str);
		if (!(*line))
			exit(errno);
		(*line) = *p->copy_line;
	}
	if (((p->quotes && !ft_strncmp(str, "", 1)) || ft_strncmp(str, "", 1)) || p->dollar_flag == 2)
	{
		if (!((*list) = ft_lstnew(str)))
			exit(errno);
	}
}

void			elem_list(char **line, t_parser *p, t_params **params, t_list **lst)
{
	(*line) = remove_spaces((*line));
	while (p->exit_status != 2 && *(*line) && (*(*line) == '<' || *(*line) == '>'))
		open_and_close_fd(line, p, params);
	(*line) = remove_spaces((*line));
	if (p->exit_status != 2 && *(*line) && *(*line) != ';' && *(*line) != '|')
		write_token_to_list(line, lst, p);
}

void			parsing(char **line, t_parser *p, t_params **params)
{
	t_list		*lst;

	lst = NULL;
	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		while (p->exit_status != 2 && !lst && *(*line) && *(*line) != ';' && *(*line) != '|')
			elem_list(line, p, params, &lst);
		(*params)->args = lst;
		while (p->exit_status != 2 && *(*line) && (*(*line) != '|' && *(*line) != ';'))
		{
			elem_list(line, p, &p->params, &lst->next);
			if (lst->next)
				lst = lst->next;
		}
	}
	if (p->exit_status != 2 && (*(*line) == ';' || *(*line) == '|'))
	{
		if (*(*line) == ';')
			(*params)->pipe_semic = 2;
		else if (*(*line) == '|')
			(*params)->pipe_semic = 1;
		(*line)++;
	}
//	(*line) = remove_spaces((*line));
//	if (p->exit_status != 2 && !p->quotes)
//	{
//		if (ft_strncmp((*line), "", 1))
//			check_unexpected_token(*line, &p->exit_status, &p->status);
//	}
}

//void			check_pipes_semicolon(char **line, t_parser *p)
//{
//	(*line) = remove_spaces((*line));
//	if (*(*line) == '|')
//		(*line)++;
//	if (ft_strncmp((*line), "", 1))
//		check_unexpected_token(*line, &p->exit_status, &p->status);
//}

void 			init_parser(t_d **data, t_parser *p, const int *status)
{
	p->copy_line = &(*data)->line;
	p->env = (*data)->env;
	p->status = *status;
	p->exit_status = (*data)->exit_status == 2 ? 1 : 0;
	p->quotes = 0;
	p->dollar_flag = 0;
}

void			parser(char **line, t_d **data, int *status)
{
	t_parser	p;

	init_parser(data, &p, status);
	while (*(*line))
	{
		(*data)->params = new_params_element();
		p.params = (*data)->params;
		parsing(line, &p, &p.params);
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
	while (p.exit_status != 2 && *(*line))
	{
		p.params->next = new_params_element();
		parsing(line, &p, &(p.params->next));
		if (!ft_lstsize(p.params->args))
		{
			params_free(&p.params, del_params_content);
			p.params = NULL;
		}
		else
		{
			if (p.exit_status == 2)
				break ;
//			if (!p.quotes)
//				check_pipes_semicolon(line, &p);
			p.params = p.params->next;
		}
	}
//	if (p.exit_status != 2 && (!ft_strncmp(*line, ";;", 2) || (*(*line) == ';' && *(*line + 1) == '\0')))
//		check_unexpected_token(*line, &p.exit_status, &p.status);
//	else if (p.exit_status != 2 && *(*line) == ';')
//		check_unexpected_token((*line) + 1, &p.exit_status, &p.status);
	if (p.status > 0 && p.exit_status == 1)
	{
		p.status = 0;
		p.exit_status = 0;
	}
	*status = p.status;
	(*data)->exit_status = p.exit_status;
}