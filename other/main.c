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

static int		programm_logic(t_d **data, int *status)
{
	char		*curr_symb;

	curr_symb = (*data)->line;
	if (*curr_symb == '\0' && (*data)->exit_status == 2)
	{
		(*data)->exit_status = 0;
		*status = 0;
	}
	while (*curr_symb)
	{
		(*data)->params = NULL;
		parser(&curr_symb, data, status);
		if (*status)
			break ;
		if (!pipes_and_one_cmd(data, status))
			return (0);
		if (*status && *curr_symb != ';')
			break ;
		if (*curr_symb == ';')
			curr_symb++;
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
