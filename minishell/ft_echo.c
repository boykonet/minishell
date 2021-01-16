/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:05:19 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/18 21:05:19 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*dollar(t_env *env, char **tmp1)
{
	char	*tmp2;
	char	*str2;
	char	*str3;

	tmp2 = *tmp1;
	while (*tmp2 != '$' && *tmp2 != '\0' && *tmp2 != ' ')
		tmp2++;
	str2 = ft_substr(*tmp1, 0, tmp2 - *tmp1);
	str3 = find_data_in_env(env, str2, 0);
	free(str2);
	if (!str3)
		str2 = ft_strdup("");
	else
		str2 = ft_strdup(str3);
	*tmp1 = --tmp2;
	return (str2);
}

char		*change_content(t_env *env, char *tmp1, char *content, int return_value)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = NULL;
	str2 = NULL;
	str3 = NULL;
	tmp1++;
	str1 = ft_substr(content, 0, tmp1 - content - 1);
	if (*tmp1 == '?')
		str2 = ft_itoa(return_value);
	else
		str2 = dollar(env, &tmp1);
	str3 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	str2 = ft_substr(tmp1, 1, ft_strlen(tmp1 + 1));
	free(content);
	content = ft_strjoin(str3, str2);
	free(str3);
	free(str2);
	return (content);
}

void		ft_echo(t_list **args, t_env *env, int return_value)
{
	t_list	*curr;
	char	*tmp1;
	int		single_quote;

	tmp1 = NULL;
	curr = (*args);
	while (curr)
	{
		single_quote = 0;
		if (*(char*)curr->content == '\'')
			single_quote = 1;
		while ((tmp1 = ft_strchr(curr->content, '$')) && !single_quote)
			curr->content = change_content(env, tmp1, curr->content, return_value);
		curr = curr->next;
	}
}
