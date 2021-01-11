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

//char		*to_tokens(t_env *env, char **line, int *quote)
//{
//	char	buff[2];
//	char	*res;
//	char	*tmp;
//	int 	escaped_quote;
//
//	tmp = NULL;
//	res = ft_strdup("");
//	ft_memset(buff, '\0', 2);
//	if (*(*line) != ' ' && *(*line))
//	{
//		escaped_quote = 0;
//		tmp = res;
//		if (*(*line) == '\\')
//		{
//			if ((*(*line + 1)) == '\'' && *quote == 1)
//				escaped_quote = 1;
//			else if ((*(*line + 1)) == '\"' && *quote == 2)
//				escaped_quote = 2;
//			(*line)++;
//		}
//		if (*(*line) == '$' && *quote != 1)
//			res = ft_strjoin(res, expand_env_arg(line, env));
//		else
//		{
//			if (*(*line) == '\\' && *quote == 0)
//				(*line)++;
//			buff[0] = *(*line);
//			res = ft_strjoin(res, buff);
//			(*line)++;
//		}
//		free(tmp);
//		if (!res)
//			return (NULL);
//		if ((*(*line) == '\'' && *quote == 1 && !escaped_quote) || (*(*line) == '\"' && *quote == 2 && !escaped_quote))
//		{
//			(*line)++;
//			*quote = 0;
//		}
//	}
//	return (res);
//}

/* функция, которая обрабатывает слова, вызывается внутри функции, которая обрабатывает скобочки и если скобочек нет */

//char			*read_tokens(char **line, t_env *env)
//{
//	char		*result;
//	char		*curr;
//	char 		*tmp;
//	int			quote;
//	int 		count_quote;
//
//	result = ft_strdup("");
//	quote = 0;
//	count_quote = 0;
//	if (*(*line) == '\'' || *(*line) == '\"')
//		quote = *(*line) == '\'' ? 1 : 2;
//	if (quote > 0)
//	{
//		while (*(*line) != ' ' && *(*line))
//		{
//			if ((*(*line) == '\'' && quote == 1) || (*(*line) == '\"' && quote == 2))
//				(*line)++;
//			while (quote > 0 && *(*line) != '\0')
//			{
//				tmp = result;
//				if (*(*line) == ' ')
//				{
//					curr = (*line);
//					while (*(*line) == ' ' && *(*line))
//						(*line)++;
//					if (!(curr = ft_substr(curr, 0, (*line) - curr)))
//					{
//						free(tmp);
//						return (NULL);
//					}
//					result = ft_strjoin(result, curr);
//					free(curr);
//				}
//				else
//				{
//					if (!(curr = to_tokens(env, line, &quote)))
//					{
//						free(tmp);
//						return (NULL);
//					}
//					result = ft_strjoin(result, curr);
//					free(curr);
//				}
//				free(tmp);
//				if (!result)
//					return (NULL);
//			}
//			if (*(*line) == '\'' || *(*line) == '\"')
//				quote = *(*line) == '\'' ? 1 : 2;
//			else
//				break ;
//		}
//	}
//	else
//	{
//		tmp = result;
//		result = to_tokens(env, line, &quote);
//		free(tmp);
//	}
//	return (result);
//}

char		*expand_env_arg(char **line, t_env *env)
{
	char	*arg;
	char 	*res;
	char 	*curr;

	res = NULL;
	if (*(*line) == '$' && (*(*line + 1) == ' ' || *(*line + 1) == '$' || *(*line + 1) == '\0'))
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
		}
		if (*(*line) == '\"' && (*(*line + 1) == ' ' || *(*line + 1) == '\0') && !spec_char)
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

char 		*return_token(char **line, t_env *env)
{
	char 	*res;
	char 	*tmp;
	char 	*curr;
	int 	spec_char;

	res = ft_strdup("");
	while (*(*line))
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
				break ;
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
	return (res);
}

t_list		*lexer(char **line, t_env *env)
{
	t_list	*tokens;
	t_list	*curr;
	char	*str;

	(*line) = remove_spaces((*line));
	if (!(str = return_token(line, env)))
		return (NULL);
	if (!(tokens = ft_lstnew(str)))
		return (NULL);
	curr = tokens;
	while (*(*line))
	{
		(*line) = remove_spaces((*line));
		if (*(*line) == '\0' || *(*line) == ';')
			break ;
		if (!(str = return_token(line, env)))
			return (NULL);
		if (!(curr->next = ft_lstnew(str)))
		{
			ft_lstclear(&tokens, &del_content);
			return (0);
		}
		curr = curr->next;
	}
	return (tokens);
}