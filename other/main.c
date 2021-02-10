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

static int		one_command(t_d **data)
{
	char		**arr;
	char		**envp;
	char		*cmd;
	int			status;

	status = 0;
	if (!check_command((*data)->params->args->content))
	{
		if ((*data)->params->in > 2)
			dup2((*data)->params->in, 0);
		if ((*data)->params->out > 2)
			dup2((*data)->params->out, 1);
		status = builtins(data, (*data)->params);
		if (status > 0 && (*data)->exit_status != 1)
			(*data)->exit_status = 2;
		dup2((*data)->origfd[0], 0);
		dup2((*data)->origfd[1], 1);
	}
	else
	{
		arr = convert_struct_to_array((*data)->params->args);
		envp = convert_env_to_arr((*data)->env);
		if (!(cmd = find_path((*data)->params->args->content,\
		find_data_in_env((*data)->env, "PATH", 0), &status)))
			if (!status)
				if (!(cmd = ft_strdup((*data)->params->args->content)))
					exit(errno);
		if (!status)
			status = create_process(data, arr, envp, cmd);
		if (status > 0)
			(*data)->exit_status = 2;
		free_string(arr);
		free_string(envp);
		free(cmd);
	}
	return (status);
}

static int 		pipes_and_one_cmd(t_d **data, int *status)
{
	if ((*data)->params && (*data)->params->next)
	{
		*status = pipes(data);
		if (*status > 0)
			(*data)->exit_status = 2;
	}
	else if ((*data)->params)
	{
		*status = one_command(data);
		if (!ft_strcmp((*data)->params->args->content, "exit") && \
				(*data)->exit_status == 1)
			return (0);
	}
	return (1);
}

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

static int 		read_and_write_cmd(t_d *data, int *status)
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
