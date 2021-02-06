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

int 			one_command(t_d **data)
{
	char 		**arr;
	char 		**envp;
	char 		*cmd;
	int 		status;

	if (!check_command((*data)->params->args->content))
	{
		status = builtins(data, (*data)->params);
		if (status > 0 && (*data)->exit_status != 1)
			(*data)->exit_status = 2;
	}
	else
	{
		arr = convert_struct_to_array((*data)->params->args);
		envp = convert_env_to_arr((*data)->env);
		if (!(cmd = find_path((*data)->params->args->content,\
		find_data_in_env((*data)->env, "PATH", 0))))
			cmd = ft_strdup((*data)->params->args->content);
		status = create_process(data, arr, envp, cmd);
		if (status > 0)
			(*data)->exit_status = 2;
		free_string(arr);
		free_string(envp);
		free(cmd);
	}
	return (status);
}

int				bla(t_d **data, int *status)
{
	char 		*curr_symb;

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
		if (*curr_symb == ';' && *(curr_symb + 1) != *curr_symb)
			curr_symb++;
		if ((*data)->params->next)
		{
			*status = pipes(data);
			if (*status > 0)
				(*data)->exit_status = 2;
		}
		else
		{
			*status = one_command(data);
			if (!ft_strcmp((*data)->params->args->content, "exit") && (*data)->exit_status == 1)
				return (0);
		}
		if (*status && *curr_symb == '\0')
			break ;
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
		print_prompt_line(data, 0);
		if ((getcharacter(0, &data->line)) < 0)
			continue ;
		if (!bla(&data, &status))
		{
			del_data_content(data);
			break ;
		}
		free(data->line);
		params_free(&data->params, del_params_content);
	}
	return (status);
}