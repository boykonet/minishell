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
#include "evaluator.h"
#include "lexic.h"

static int		programm_logic(t_d **data, int *status)
{
	t_params 	*curr;
	t_params	*aaa;
	t_list		*a;

	if (*(*data)->line == '\0' && (*data)->exit_status == 2)
	{
		(*data)->exit_status = 0;
		*status = 0;
	}
	*status = lexic((*data)->line);
	if (*status)
	{
		(*data)->exit_status = 2;
		return (1);
	}
	(*data)->params = parser((*data)->line);
	aaa = (*data)->params;
	while (aaa)
	{
		a = aaa->args;
		while (a)
		{
			ft_putendl_fd(a->content, 1);
			a = a->next;
		}
		aaa = aaa->next;
	}
	curr = (*data)->params;
	while (!(*status) && curr)
	{
		evaluator(data, curr, status);
		if (!pipes_and_one_cmd(data, &curr, status))
			return (0);
	}
	return (1);
}

static int		read_and_write_cmd(t_d *data, int *status)
{
	print_prompt_line(data, 0);
	if (!(getcharacter(0, &data->line)))
	{
		*status = 0;
		del_data_content(data);
		return (0);
	}
	if (!programm_logic(&data, status))
	{
		del_data_content(data);
		return (0);
	}
	return (1);
}

int				main(int argc, char **argv, char **envp)
{
	t_d			*data;
	static int	status;

	status = 0;
	if (!(data = malloc(sizeof(t_d))))
		exit(errno);
	init_data(&data);
	data->argc = argc;
	data->argv = copy_array(argv);
	data->env = copy_envp_to_struct(envp);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	while (TRUE)
	{
		data->line = NULL;
		data->params = NULL;
		if (!read_and_write_cmd(data, &status))
			break ;
		free(data->line);
		params_free(&data->params, del_params_content);
	}
	return (status);
}
