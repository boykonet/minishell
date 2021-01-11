/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_struct_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:05:50 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/10 14:05:50 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list		*convert_array_to_struct(char **array);

char		**convert_struct_to_array(t_list *lst)
{
	t_list	*curr;
	char	**arr;
	int		i;

	arr = NULL;
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

int main(int argc, char *argv[], char **env)
{
	t_list	*lst;
	char 	**arr;
	int		i;

	i = 0;

	lst = convert_array_to_struct(env);
	arr = convert_struct_to_array(lst);
	while (arr[i])
	{
		printf("%s\n", arr[i++]);
	}
	return 0;
}
