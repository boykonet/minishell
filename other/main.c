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

	status = 0;
	if (!check_command((*data)->params->args->content))
		status = builtins((*data)->params, &(*data)->env, &status, &(*data)->exit_status);
	else
	{
		arr = convert_struct_to_array((*data)->params->args);
		envp = convert_env_to_arr((*data)->env);
		if (!(cmd = find_path((*data)->params->args->content,find_data_in_env((*data)->env, "PATH", 0))))
			cmd = ft_strdup((*data)->params->args->content);
		status = create_process(arr, envp, cmd);
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
	while (*curr_symb)
	{
		(*data)->params = NULL;
		parser(&curr_symb, &(*data)->params, (*data)->env, status);
		if (!*status && *curr_symb == ';' && *(curr_symb + 1) != *curr_symb)
			curr_symb++;
		else if (!*status && *curr_symb == ';' && *(curr_symb + 1) == *curr_symb)
		{
			ft_printf("-minishell: syntax error near unexpected token `%s'\n", ";;");
			*status = 258;
		}
		if (!*status && (*data)->params->next)
			*status = pipes((*data)->params, &(*data)->env, status, &(*data)->exit_status);
		else if (!*status)
		{
			*status = one_command(data);
			if ((*data)->exit_status)
				return (0);
		}
		params_free(&(*data)->params, del_params_content);
		if (*status)
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
	init_data(data);
	data->argc = argc;
	data->argv = copy_array(argv);
	data->env = copy_envp_to_struct(envp);
	while (TRUE)
	{
		data->line = NULL;
		print_prompt_line(data->env, &data->username, &data->folder);
		if ((getcharacter(0, &data->line)) < 0)
			return (errno);
		if (!bla(&data, &status))
		{
			del_data_content(data);
			return (status);
		}
		free(data->line);
	}
}