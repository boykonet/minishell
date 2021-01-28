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

#include "minishell.h"
#include "parser.h"
#include "builtins.h"
#include "other.h"

void 			prompt_line(t_env *env, char **user_name, char **folder)
{
	char 		*line;

	if ((line = find_data_in_env(env, "USER", 0)))
	{
		if (*user_name)
			free(*user_name);
		*user_name = ft_strdup(line);
	}
	if ((line = find_data_in_env(env, "PWD", 0)))
	{
		if (*folder)
			free(*folder);
		if ((ft_strncmp(find_data_in_env(env, "HOME", 0), line, ft_strlen(line))))
			*folder = ft_strdup(ft_strrchr(line, '/'));
		else
			*folder = ft_strdup(line);
	}
	if (ft_strlen(*folder) == 1)
		ft_printf("\e[1;36m%s\e[0m ", *folder);
	else if (!(ft_strncmp(find_data_in_env(env, "HOME", 0), *folder, ft_strlen(*folder))))
		ft_printf("\e[1;36m~\e[0m ");
	else
		ft_printf("\e[1;36m%s\e[0m ", *folder + 1);
	ft_printf("\e[1;36m%s\e[0m$ ", *user_name);
}

int				bla(t_d **data, int *status)
{
	char 		*curr_symb;
//	t_params	*d_p;
//	t_list		*list;

	curr_symb = (*data)->line;
	while (*curr_symb)
	{
		(*data)->params = NULL;
		if (!parser(&curr_symb, &(*data)->params, (*data)->env, status))
			return (1);
		if (*curr_symb == ';' && *(curr_symb + 1) != *curr_symb)
			curr_symb++;
		else if (*curr_symb == ';' && *(curr_symb + 1) == *curr_symb)
		{
			ft_printf("-minishell: syntax error near unexpected token `%s'\n", ";;");
			*status = 258;
			return (1);
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
		if ((*data)->params->next)
			pipes((*data)->params, &(*data)->env, status);
		else
		{
			if (!builtins((*data)->params, &(*data)->env, status))
			{
				free_data(*data);
				return (0);
			}
		}
		params_free(&(*data)->params, del_params_content);
	}
	return (2);
}

int				main(int argc, char **argv, char **envp)
{
	t_d 		*data;
	static int	status;
	int         a;

	status = 0;
	if (!(data = malloc(sizeof(t_d))))
		exit(errno);
	init_data(data);
	data->argc = argc;
	data->argv = copy_array(argv);
	data->env = copy_envp_to_struct(envp);
	while (TRUE)
	{
		prompt_line(data->env, &data->user_name, &data->folder);
		if ((getcharacter(0, &data->line)) < 0)
			return (errno);
		a = bla(&data, &status);
		if (!a)
			return (status);
		else if (a == 1)
			continue ;
		free(data->line);
	}
}
