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

void			write_token_to_list(char **line, t_list **list, \
									t_env *env, int *status)
{
	char 		*str;

	str = return_token(line, env, status);
	if (!((*list) = ft_lstnew(str)))
		exit(errno);
}

t_params		*check_redir_line(char **line, t_env *env, \
									t_params **res, int *status)
{
	if (!open_and_close_fd(line, res, env, status))
		params_free(res, del_params_content);
	if (!*res)
		return (NULL);
	return (*res);
}

t_list			*first_elem_list(char **line, t_params **res, \
								t_env *env, int *status)
{
	t_list 		*lst;

	lst = NULL;
	(*line) = remove_spaces((*line));
	while (res && (*(*line) == '<' || *(*line) == '>'))
		check_redir_line(line, env, res, status);
	if (res)
	{
		(*line) = remove_spaces((*line));
		write_token_to_list(line, &(*res)->args, env, status);
		if (!check_unexpected_token((char**)&((*res)->args)->content))
		{
			ft_putstr_fd("-minishell: syntax error near unexpected token `", 1);
			ft_putstr_fd((*res)->args->content, 1);
			ft_putendl_fd("'", 1);
			*status = 258;
			params_free(res, del_params_content);
			return (NULL);
		}
		lst = (*res)->args;
	}
	return (lst);
}

t_params		*parsing(char **line, t_env *env, int *status)
{
	t_params	*res;
	t_list		*lst;

	res = NULL;
	new_params_element(&res);
	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		if (!(lst = first_elem_list(line, &res, env, status)))
			if (!res)
				return (NULL);
		while (res && *(*line) && (*(*line) != '|' && *(*line) != ';'))
		{
			(*line) = remove_spaces((*line));
			if (*(*line) == '<' || *(*line) == '>')
				check_redir_line(line, env, &res, status);
			else if (*(*line) && *(*line) != '|' && *(*line) != ';')
			{
				(*line) = remove_spaces((*line));
				write_token_to_list(line, &lst->next, env, status);
				lst = lst->next;
			}
		}
	}
	return (res);
}

int 			parser(char **line, t_params **params, t_env *env, int *status)
{
	t_params 	*curr;

	if (*(*line))
	{
		(*params) = parsing(line, env, status);
		if (*status > 0 && !(*params))
			return (0);
//		if (*(*line) == '|' && *(*line + 1) == '|')
//		{
//			ft_printf("-minishell: syntax error near unexpected "
//					  "token `%s'\n", (*res)->args->content);
//			*status = 258;
//			params_free(res, del_params_content);
//		}
		if (*(*line) == '|')
			(*line)++;
		curr = (*params);
		while (curr && *(*line) && *(*line) != ';')
		{
			curr->next = parsing(line, env, status);
			if (*status > 0 && !curr->next)
				return (0);
			if (*(*line) == '|')
				(*line)++;
			curr = curr->next;
		}
		if (*status > 0 && (*params))
			*status = 0;
	}
	return (1);
}