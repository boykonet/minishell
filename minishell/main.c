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

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

int				main(int argc, char **argv, char **envp)
{
	t_data 		*data;
	t_params	*d_p;
	t_list		*list;
	static int	status;
	char 		*curr_symb;

	status = 0;
	data = malloc(sizeof(t_data));
	init_data(data);
	if (!(data->env = copy_envp_to_struct(envp)))
	{
		free_data(data);
		return (-1);
	}
	while (TRUE)
	{
		write(1, "minishell$ ", ft_strlen("minishell$ "));
		if ((getcharacter(0, &data->line)) < 0)
			return (-1);
		curr_symb = data->line;
		while (*curr_symb)
		{
			data->params = NULL;
			lexer(&curr_symb, &data->params, data->env, &status);
			if (status > 0)
				break ;
			if (*curr_symb == ';')
				curr_symb++;
			d_p = data->params;
			while (d_p)
			{
				list = d_p->args;
				while (list)
				{
					printf("%s\n", list->content);
					list = list->next;
				}
				d_p = d_p->next;
			}
//				builtins(&params, ch, &status);
			params_free(&data->params, del_params_content);
		}
		status = 0;
		free(data->line);
	}
	return (status);
	//     echo -n '<   "qwerty"   >'     4qwerty4     '<   qwerty   >''<   "qwerty"   >'    4qwerty4    '<   qwerty   >' >> file.txt | grep -lE "main"
}
