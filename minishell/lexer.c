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

#include "../minishell.h"

char		*expand_env_arg(char **line, t_env *env, int *status)
{
	char	*arg;
	char 	*res;
	char 	*curr;

	res = NULL;
	if (*(*line) == '$' && (*(*line + 1) == ' ' || *(*line + 1) == '$' || \
		*(*line + 1) == '\\' || *(*line + 1) == '\0'))
	{
		if (!(res = ft_strdup("$")))
			exit(errno);
		(*line)++;
	}
	else if (!ft_strncmp(*line, "$?", 2))
	{
		res = ft_itoa(*status);
		(*line) = *(line) + 2;
		if (!res)
			exit(errno);
	}
	else
	{
		(*line)++;
		curr = (*line);
		while (*curr && (ft_isalnum(*curr) || *curr == '_'))
			curr++;
		if (!(arg = ft_substr((*line), 0, curr - (*line))))
			exit(errno);
		res = find_data_in_env(env, arg, 0);
		if (!res)
			res = ft_strdup("");
		else
			res = ft_strdup(res);
		free(arg);
		(*line) = curr;
		if (!res)
			exit(errno);
	}
	return (res);
}

char		*remove_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

int 		check_redir(char **line)
{
	char 	*curr_str;
	char 	*str;
	char	symb;
	int 	r;

	r = -1;
	if (*(*line) == '<' || *(*line) == '>')
	{
		curr_str = (*line);
		symb = *(*line);
		while (*curr_str && *curr_str == symb && *curr_str != ' ')
			curr_str++;
		if (!(str = ft_substr((*line), 0, curr_str - (*line))))
			exit(errno);
		r = number_of_redirect(str);
		free(str);
	}
	return (r);
}

void			write_token_to_list(char **line, t_list **list, t_env *env, int *status)
{
	char 		*str;

	str = return_token(line, env, status);
	if (!((*list) = ft_lstnew(str)))
		exit(errno);
}

t_params		*lex(char **line, t_env *env, int *status)
{
	t_params	*res;
	t_list		*lst;

	res = new_params_element();
	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		(*line) = remove_spaces((*line));
		while (*(*line) == '<' || *(*line) == '>')
		{
			if (!open_and_close_fd(line, &res, env, status))
			{
				params_free(&res, del_params_content);
				return (NULL);
			}
		}
		write_token_to_list(line, &res->args, env, status);
		lst = res->args;
		while (*(*line) && *(*line) != '|' && *(*line) != ';')
		{
			(*line) = remove_spaces((*line));
			if (*(*line) == '<' || *(*line) == '>')
			{
				if (!open_and_close_fd(line, &res, env, status))
				{
					params_free(&res, del_params_content);
					return (NULL);
				}
			}
			else if (*(*line) && *(*line) != '|' && *(*line) != ';')
			{
				write_token_to_list(line, &lst->next, env, status);
				lst = lst->next;
			}
		}
		if (*status > 0)
		{
			params_free(&res, del_params_content);
			return (NULL);
		}
	}
	return (res);
}

int 			lexer(char **line, t_params **params, t_env *env, int *status)
{
	t_params 	*curr;

	if (*(*line))
	{
		(*params) = lex(line, env, status);
		if (*(*line) == '|')
			(*line)++;
		curr = (*params);
		while (*(*line) && *(*line) != ';')
		{
			if (*status > 0)
				return (0);
			curr->next = lex(line, env, status);
			if (*(*line) == '|')
				(*line)++;
			curr = curr->next;
		}
	}
	return (1);
}