/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:15:41 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 16:15:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_data(t_data *data)
{
	if (envp_dupl)
		free_str(env_dupl);
	free(envp_dupl);
}

void		init_data(t_data *data)
{
	data->envp_dupl = NULL;
	data->envp_size = 0;
	data->redir_double_rigth = 0;
	data->redir_left = 0;
	data->redir_rigth = 0;
}

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void		free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void		del_content(void *content)
{
	if (content)
		free(content);
}

t_list		*copy_in_struct(char **str)
{
	t_list	*head;
	t_list	*curr;
	size_t	str_size;
	size_t	i;

	i = 0;
	if (!(head = ft_lstnew(ft_strdup(str[i++]))))
		return (NULL);
	curr = head;
	str_size = number_of_lines(str);
	while (i < str_size)
	{
		if (!(curr->next = ft_lstnew(ft_strdup(str[i++]))))
		{
			ft_lstclear(&head, &del_content);
			return (NULL);
		}
		curr = curr->next;
	}
	return (head);
}

int			main(int argc, char **argv, char **envp)
{
	t_str	s_str;
	t_data	data;

	init_s_str(&s_str);
	init_data(&data);
//	data.envp_size = number_of_lines(envp);
	if (!(s_str.args = copy_in_struct(envp)))
	{
		strerror(errno);
		return (-1);
	}
	while (TRUE)
	{
		gnl();
		parser(&data);
		builtins(&data);
	}
	return (0);
}
