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
	if (*(*line) == '$' && (*(*line + 1) == ' ' || *(*line + 1) == '$' || *(*line + 1) == '\\' || *(*line + 1) == '\0'))
	{
		res = ft_strdup("$");
		(*line)++;
	}
	else if (*(*line) == '$' && *(*line + 1) == '?')
	{
		if (!(arg = ft_itoa(*status)))
			return (NULL);
		res = ft_strdup(arg);
		free(arg);
		if (!res)
			return (NULL);
		(*line) = *(line) + 2;
	}
	else
	{
		(*line)++;
		curr = (*line);
		while (*curr && (ft_isalnum(*curr) || *curr == '_'))
			curr++;
		if (!(arg = ft_substr((*line), 0, curr - (*line))))
			return (NULL);
		res = find_data_in_env(env, arg, 0);
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

char		*tokens_with_double_quotes(char **line, t_env *env, int *status)
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
			if (!(curr = expand_env_arg(line, env, status)))
			{
				free(tmp);
				return (NULL);
			}
			token = ft_strjoin(token, curr);
			free(curr);
		}
		else
			token = append_to_array(token, *(*line)++);
		free(tmp);
		if (!(token))
			return (NULL);
	}
	return (token);
}

char		*handling_tokens_with_quotes(char **line, t_env *env, int *status)
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
		if (!(res = tokens_with_double_quotes(line, env, status)))
			return (NULL);
	}
	return (res);
}

char 		*return_token(char **line, t_env *env, int *status)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;
	int 	spec_char;

	res = ft_strdup("");
	while (*(*line) && *(*line) != ' ' && *(*line) != ';')
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
			curr = handling_tokens_with_quotes(line, env, status);
			res = ft_strjoin(res, curr);
			free(tmp);
			free(curr);
		}
		else
		{
			if (*(*line) == '$' && !spec_char)
			{
				if (!(curr = expand_env_arg(line, env, status)))
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
	init_params(&params);
	return (params);
}

int 		ccc(char **line, t_params **params, t_env *env, int *status)
{
	if (check_redir(line) == 0)
		redir(line, env, &((*params)->in), status);
	else if (check_redir(line) == 1)
		redir(line, env, &((*params)->out), status);
	else if (check_redir(line) == 2)
		redir(line, env, &((*params)->err), status);
	if (status == 0)
		return (1);
	return (0);
}

t_params		*lex(char **line, t_env *env, int *status)
{
	t_params	*res;
	t_list		*lst;
	char		*str;

	if (!(res = params_new()))
		return (NULL);
	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		(*line) = remove_spaces((*line));
		while (*(*line) == '<' || *(*line) == '>')
			ccc(line, &res, env, status);
		if (*status == 0 && !(str = return_token(line, env, status)))
		{
			params_free(&res, del_params_content);
			return (NULL);
		}
		if (*status == 0 && !(res->args = ft_lstnew(str)))
		{
			params_free(&res, del_params_content);
			return (NULL);
		}
		lst = res->args;
		while (*status == 0 && *(*line) && *(*line) != '|' && *(*line) != ';')
		{
			str = NULL;
			(*line) = remove_spaces((*line));
			if (*(*line) == '<' || *(*line) == '>')
				ccc(line, &res, env, status);
			else
			{
				if (!(str = return_token(line, env, status)))
				{
					params_free(&res, del_params_content);
					return (NULL);
				}
				if (!(lst->next = ft_lstnew(str)))
				{
					params_free(&res, del_params_content);
					return (NULL);
				}
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
		if (!((*params) = lex(line, env, status)))
			return (0);
		if (*(*line) == '|')
			(*line)++;
		curr = (*params);
		while (*(*line) && *(*line) != ';')
		{
			if (!(curr->next = lex(line, env, status)))
			{
				params_free(params, del_params_content);
				return (0);
			}
			if (*(*line) == '|')
				(*line)++;
			curr = curr->next;
		}
	}
	return (1);
	//			if (*(*line) == ';' && *(*line + 1) == ';')
//				error_handling(NULL, ";;", );
}