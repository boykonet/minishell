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

void		del_content(void *content)
{
	if (content)
		free(content);
}

void		free_data(t_data *data)
{
	if (data->envp_dupl)
		ft_lstclear(&data->envp_dupl, &del_content);
}

void		free_params(t_params *params)
{
	if (params->args)
		ft_lstclear(&params->args, &del_content);
	if (params->command)
		free(params->command);
	if (params->flag)
		free(params->flag);
	if (params->redir)
		free(params->redir);
	if (params->name_fd)
		free(params->name_fd);
}

void		init_data(t_data *data)
{
	data->envp_dupl = NULL;
	data->pwd = NULL;
	data->envp_size = 0;
	data->redir_left = 0;
	data->redir_rigth = 0;
	data->redir_double_rigth = 0;
}

void		init_params(t_str *params)
{
	params->args = NULL;
	params->curr = NULL;
	params->command = NULL;
	params->flag = NULL;
	params->redir = NULL;
	params->name_fd = NULL;
	params->args_size = 0;
}

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void		free_string(char **str)
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

t_list		*copy_in_list(char **str)
{
	t_list	*head;
	t_list	*curr;
	size_t	i;

	i = 0;
	if (!(head = ft_lstnew(ft_strdup(str[i++]))))
		return (NULL);
	curr = head;
	curr = curr->next;
	while (str[i])
	{
		if (!(curr = ft_lstnew(ft_strdup(str[i]))))
		{
			ft_lstclear(&head, &del_content);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (head);
}

void		wait_line(char *)
{
	char	*curr_location;

	write(1, curr_location, ft_strlen(curr_location));
	write(1, " $>", 3);
}

int			main(int argc, char **argv, char **envp)
{
	t_params	params;
	t_data		data;
	char		*line;

	init_params(&params);
	init_data(&data);
	if (!(data.envp_dupl = copy_in_list(envp)))
	{
		strerror(errno);
		return (-1);
	}
	while (TRUE)
	{
		write(1, "minishell $>", 12);
		if (get_next_line(0, &line) < 0)
			return (-1);
		parser(&data, &params, line);
		builtins(&data, &params);
		free(line);
		free_params(&params);
		free_data(&data);
	}
	return (0);
}
