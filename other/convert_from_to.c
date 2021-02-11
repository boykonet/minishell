/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_from_to.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:21:26 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/10 14:21:26 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

char		**convert_struct_to_array(t_list *lst)
{
	t_list	*curr;
	char	**arr;
	int		i;

	curr = lst;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	if (!(arr = ft_calloc(i + 1, sizeof(char*))))
		return (NULL);
	arr[i] = NULL;
	i = 0;
	while (lst)
	{
		if (!(arr[i++] = ft_strdup(lst->content)))
		{
			free_string(arr);
			return (NULL);
		}
		lst = lst->next;
	}
	return (arr);
}

char		**convert_env_to_arr(t_env *env)
{
	int		i;
	char	**arr;
	char	*tmp;

	i = ft_lstsize_env(env);
	if (!(arr = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			if (!(tmp = ft_strjoin(env->name, "=")))
				exit(errno);
			arr[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			arr[i] = ft_strdup(env->name);
		if (!arr[i])
			exit(errno);
		i++;
		env = env->next;
	}
	return (arr);
}
