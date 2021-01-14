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

char		*expand_env_arg(char **line, t_env *env)
{
	char	*arg;
	char 	*res;
	char 	*curr;

	res = NULL;
	if (*(*line) == '$' && (*(*line + 1) == ' ' || *(*line + 1) == '$' || *(*line + 1) == '\\' || *(*line + 1) == '\0'))
	{
		res = ft_strdup("$");
		(*line)++;
	}
	else
	{
		(*line)++;
		curr = (*line);
		while (*curr && (ft_isalnum(*curr) || *curr == '_'))
			curr++;
		if (!(arg = ft_substr((*line), 0, curr - (*line))))
			return (NULL);
		find_data_in_env(env, arg, &res, 0);
		if (!res)
			res = ft_strdup("");
		else
			res = ft_strdup(res);
		free(arg);
		if (!res)
			return (NULL);
		(*line) = curr;
	}
	return (res);
}

char		*remove_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char		*append_to_array(char *src, char symb)
{
	char 	*dst;
	int 	i;

	i = 0;
	if (!(dst = ft_calloc(ft_strlen(src) + 2, sizeof(char))))
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = symb;
	dst[++i] = '\0';
	return (dst);
}

char		*tokens_with_single_quotes(char **line)
{
	char 	*token;
	char 	*curr;

	curr = (*line);
	curr++;
	while (*curr)
	{
		if (*curr == '\'')
			break ;
		curr++;
	}
	token = ft_substr((*line), 1, curr - (*line) - 1);
	(*line) = ++curr;
	return (token);
}

char		*tokens_with_double_quotes(char **line, t_env *env)
{
	char 	*token;
	char	*tmp;
	char 	*curr;
	int 	spec_char;

	token = ft_strdup("");
	(*line)++;
	while (*(*line))
	{
		tmp = token;
		spec_char = 0;
		if (*(*line) == '\\')
		{
			if (*(*line + 1) == '\"' || *(*line + 1) == '$')
			{
				(*line)++;
				spec_char = 1;
			}
			else if (*(*line + 1) == '!')
				spec_char = 1;
		}
		if (*(*line) == '\"' && (*(*line + 1) == ' ' || *(*line + 1) == '\0' \
			|| *(*line + 1) == '\"' || *(*line + 1) == '\'') && !spec_char)
		{
			(*line)++;
			break ;
		}
		if (*(*line) == '$' && !spec_char)
		{
			if (!(curr = expand_env_arg(line, env)))
			{
				free(tmp);
				return (NULL);
			}
			token = ft_strjoin(token, curr);
			free(curr);
		}
		else
			token = append_to_array(token, *(*line));
		free(tmp);
		if (!(token))
			return (NULL);
		(*line)++;
	}
	return (token);
}

char		*handling_tokens_with_quotes(char **line, t_env *env)
{
	char 	*res;

	res = NULL;
	if (*(*line) == '\'')
	{
		if (!(res = tokens_with_single_quotes(line)))
			return (NULL);
	}
	else if (*(*line) == '\"')
	{
		if (!(res = tokens_with_double_quotes(line, env)))
			return (NULL);
	}
	return (res);
}

char 		*return_token(char **line, t_params **params, t_env *env)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;
	int 	spec_char;

	res = ft_strdup("");
	while (*(*line))
	{
		if (!(*(*line) == '>' || *(*line) == '<'))
		{
			tmp = res;
			spec_char = 0;
			if (*(*line) == '\\')
			{
				(*line)++;
				spec_char = 1;
			}
			if ((*(*line) == '\'' || *(*line) == '\"') && !spec_char)
			{
				curr = handling_tokens_with_quotes(line, env);
				res = ft_strjoin(res, curr);
				free(tmp);
				free(curr);
			}
			else
			{
				if (*(*line) == ' ' || *(*line) == ';')
					break;
				if (*(*line) == '$' && !spec_char)
				{
					if (!(curr = expand_env_arg(line, env)))
					{
						free(tmp);
						return (NULL);
					}
				}
				else
				{
					if (!(curr = ft_calloc(2, sizeof(char))))
					{
						free(tmp);
						return (NULL);
					}
					if (*(*line) == '\\')
						(*line)++;
					curr[0] = *(*line)++;
				}
				res = ft_strjoin(res, curr);
				free(tmp);
				free(curr);
			}
			if (!res)
				return (NULL);
		}
		else
		{
			if (check_redir(line) == 0)
				redir(line, &((*params)->in));
			else if (check_redir(line) == 1)
				redir(line, &((*params)->out));
			else if (check_redir(line) == 2)
				redir(line, &((*params)->err));
		}

	}
	return (res);
}

int 		check_redir(char **line)
{
	char 	*curr_str;
	char 	*str;
	char	symb;
	int 	r;

	r = -1;
	if ((*(*line) == '<' || *(*line) == '>' || \
	(*(*line) == '1' && *(*line + 1) == '>') || \
	(*(*line) == '2' && *(*line + 1) == '>')))
	{
		curr_str = (*line);
		symb = *(*line);
		while (*curr_str && *curr_str == symb && *curr_str != ' ')
			curr_str++;
		str = ft_substr((*line), 0, curr_str - (*line));
		r = redirects(str);
		free(str);
	}
	return (r);
}

t_params	*params_new(void)
{
	t_params	*params;

	if (!(params = malloc(sizeof(t_params))))
		return (NULL);
	params = init_params(params);
	return (params);
}

void 			params_free(t_params **params, void (*del)(t_params *))
{
	t_params	*curr;

	while ((*params) != NULL)
	{
		curr = (*params)->next;
		if (del)
			(*del)((*params));
		free((*params));
		(*params) = curr;
	}
}

t_params		*lex(char **line, t_env *env)
{
	t_params	*res;
	t_list		*lst;
	char		*str;

	(*line) = remove_spaces((*line));
	if (!(res = params_new()))
		return (NULL);
	if (*(*line) == '\0' || *(*line) == '|' || *(*line) == ';')
		return (res);
	if (!(res->cmd = return_token(line, &res, env)))
	{
		params_free(&res, free_params);
		return (NULL);
	}
	while (*(*line))
	{
		(*line) = remove_spaces((*line));
		if (*(*line) == '\0' || *(*line) == '|' || *(*line) == ';')
			break ;
		if (!(str = return_token(line, &res, env)))
			return (NULL);
		if (!(res->args = ft_lstnew(str)))
		{
			return (NULL);
		}
		lst = res->args;
		while (*(*line))
		{
			(*line) = remove_spaces((*line));
			if (*(*line) == '\0' || *(*line) == '|' || *(*line) == ';')
				break ;
			if (!(str = return_token(line, &res, env)))
				return (NULL);
			if (!(lst->next = ft_lstnew(str)))
			{
				return (NULL);
			}
			lst = lst->next;
		}
	}
	return (res);
}

int 			lexer(char **line, t_params **params, t_env *env)
{
	t_params 	*curr;
	int 		status;

	status = 0;
	while (*(*line))
	{
		(*params) = lex(line, env);
		if (*(*line) == ';')
			break ;
		if (*(*line) == '|')
			(*line)++;
		curr = (*params);
		while (*(*line) && *(*line) != ';')
		{
			if (!(curr->next = lex(line, env)))
			{
				params_free(params, free_params);
				return (-1);
			}
			if (*(*line) == ';')
				return (status);
			if (*(*line) == '|')
				(*line)++;
			curr = curr->next;
		}
	}
	return (status);
	//			if (*(*line) == ';' && *(*line + 1) == ';')
//				error_handling(NULL, ";;", );
}