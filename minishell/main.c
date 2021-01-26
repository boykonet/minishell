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

char 			**copy_array(char **src)
{
	char 		**res;
	int 		i;

	i = number_of_lines(src);
	if (!(res = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	while (src[i])
	{
		if (!(res[i] = ft_strdup(src[i])))
		{
			free_string(res);
			exit(errno);
		}
		i++;
	}
	return (res);
}

int				bla(t_d **data, int *status)
{
	char 		*curr_symb;
	t_params	*d_p;
	t_list		*list;

	curr_symb = (*data)->line;
	while (*curr_symb)
	{
		(*data)->params = NULL;
		if (!parser(&curr_symb, &(*data)->params, (*data)->env, status))
			return (0);
		if (*curr_symb == ';' && *(curr_symb + 1) != *curr_symb)
			curr_symb++;
		else if (*curr_symb == ';' && *(curr_symb + 1) == *curr_symb)
		{
			ft_printf("-minishell: syntax error near unexpected token `%s'\n", ";;");
			*status = 258;
			return (0);
		}
//		d_p = (*data)->params;
//		while (d_p)
//		{
//			list = d_p->args;
//			while (list)
//			{
//				printf("%s\n", list->content);
//				list = list->next;
//			}
//			d_p = d_p->next;
//		}
		builtins((*data)->params, &(*data)->env, status);
		params_free(&(*data)->params, del_params_content);
	}
	return (1);
}

int				main(int argc, char **argv, char **envp)
{
	t_d 		*data;
	static int	status;

	status = 0;
	if (!(data = malloc(sizeof(t_d))))
		exit(errno);
	init_data(data);
	data->argc = argc;
	data->argv = copy_array(argv);
	data->env = copy_envp_to_struct(envp);
	while (TRUE)
	{
		write(1, "minishell$ ", ft_strlen("minishell$ "));
		if ((getcharacter(0, &data->line)) < 0)
			return (-1);
		if (!bla(&data, &status))
			continue ;
		free(data->line);
	}
	return (status);
}
