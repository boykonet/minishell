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
		if (!(arg = ft_itoa(*status)))
			exit(errno);
		res = ft_strdup(arg);
		free(arg);
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

char		*append_to_array(char *src, char symb)
{
	char 	*dst;
	int 	i;

	i = 0;
	if (!(dst = ft_calloc(ft_strlen(src) + 2, sizeof(char))))
		exit(errno);
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
	if (!token)
		exit(errno);
	return (token);
}

char		*tokens_with_double_quotes(char **line, t_env *env, int *status)
{
	char 	*token;
	char	*tmp;
	char 	*curr;
	int 	spec_char;

	if (!(token = ft_strdup("")))
		exit(errno);
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
			curr = expand_env_arg(line, env, status);
			token = ft_strjoin(token, curr);
			free(curr);
			if (!token)
				exit(errno);
		}
		else
			token = append_to_array(token, *(*line)++);
		free(tmp);
	}
	return (token);
}

char		*handling_tokens_with_quotes(char **line, t_env *env, int *status)
{
	char 	*res;

	res = NULL;
	if (*(*line) == '\'')
		res = tokens_with_single_quotes(line);
	else if (*(*line) == '\"')
		res = tokens_with_double_quotes(line, env, status);
	return (res);
}

char 		*return_token(char **line, t_env *env, int *status)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;
	int 	spec_char;

	if (!(res = ft_strdup("")))
		exit(errno);
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
				curr = expand_env_arg(line, env, status);
			else
			{
				if (!(curr = ft_calloc(2, sizeof(char))))
				{
					free(tmp);
					exit(errno);
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
			exit(errno);
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

t_params	*new_params_element(void)
{
	t_params	*params;

	if (!(params = malloc(sizeof(t_params))))
		exit(errno);
	init_params(&params);
	return (params);
}

int 		open_and_close_fd(char **line, t_params **params, t_env *env, int *status)
{
	if (check_redir(line) == 0)
		reopen_fd(line, env, &((*params)->in), status);
	else if (check_redir(line) == 1)
		reopen_fd(line, env, &((*params)->out), status);
	else if (check_redir(line) == 2)
		reopen_fd(line, env, &((*params)->err), status);
	if (*status == 0)
		return (1);
	return (0);
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
	char		*str;

	res = new_params_element();
	if (*(*line) && *(*line) != '|' && *(*line) != ';')
	{
		(*line) = remove_spaces((*line));
		while (*(*line) == '<' || *(*line) == '>')
			open_and_close_fd(line, &res, env, status);
		if (*status > 0)
		{
			params_free(&res, del_params_content);
			return (NULL);
		}
		write_token_to_list(line, &res->args, env, status);
		lst = res->args;
		while (*status == 0 && *(*line) && *(*line) != '|' && *(*line) != ';')
		{
			str = NULL;
			(*line) = remove_spaces((*line));
			if (*(*line) == '<' || *(*line) == '>')
				open_and_close_fd(line, &res, env, status);
			else
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