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
#include "utils.h"
#include "evaluator.h"
#include "lexic.h"

static int		command_work(t_d **data, int *status)
{
	t_params	*curr;

	while ((*data)->params)
	{
		curr = split_par(&(*data)->params, count_params((*data)->params));
		logname_folder_home((*data)->env, &(*data)->logname, \
			&(*data)->folder, &(*data)->home);
		evaluator(data, &curr, status);
		if (!(*status) && (*data)->exit_status != 2)
		{
			if (!pipes_and_one_cmd(data, curr, status))
			{
				ft_putendl_fd("exit", 1);
				if ((*data)->exit_status == 2)
					err_exit(curr->args->next->content, *status);
				params_free(&curr, del_params_content);
				return (0);
			}
		}
		params_free(&curr, del_params_content);
	}
	return (1);
}

static int		programm_logic(t_d **data, int *status)
{
	int			stat;

	if (ft_strcmp(remove_spaces((*data)->line), ""))
	{
		if ((stat = lexic((*data)->line)) > 0)
		{
			*status = stat;
			(*data)->exit_status = 2;
			return (1);
		}
		(*data)->params = parser((*data)->line);
		if (!command_work(data, status))
			return (0);
	}
	return (1);
}

static int		read_and_write_cmd(t_d *data, int *status)
{
	logname_folder_home(data->env, &data->logname, &data->folder, &data->home);
	print_prompt_line(data, 0);
	if (!(getcharacter(0, &data->line)))
	{
		*status = 0;
		ft_putendl_fd("exit", 1);
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
