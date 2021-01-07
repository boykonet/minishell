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

void		free_params(t_params *params)
{
	if (params->cmd)
		free(params->cmd);
	if (params->args)
		free_string(&params->args);
	if (params->redir_in)
		free(params->redir_in);
	if (params->redir_out)
		free(params->redir_out);
	if (params->redir_err)
		free(params->redir_err);
	if (params->name_in)
		free(params->name_in);
	if (params->name_out)
		free(params->name_out);
	if (params->name_err)
		free(params->name_err);
}

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void		wait_line(char *str)
{
/* chochu chtoby bylo tak: ~/minishell/minishell$*/
//	char	*curr_location;
//	int		i;

	/* i = 0; */
	/* while (i < 2) */
	/* { */

	/* } */
//	write(1, curr_location, ft_strlen(curr_location));
	write(1, str, ft_strlen(str));
}

int				main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_params	params;
	t_fd		fd;
	t_list		*tokens;
	t_list 		*cmd_args;
	static int	status;
	char		*line;
	char 		*curr;

	if (!(env = copy_envp_to_struct(envp)))
		return (-1);
	while (TRUE)
	{
		line = NULL;
		wait_line("minishell$ ");

		if ((get_next_line(0, &line)) < 0)
			return (-1);
		curr = line;
		while (*curr)
		{
			tokens = NULL;
			init_params(&params);
			init_fd(&fd);

			tokens = lexer(&curr, env);
			if (*curr == ';')
				curr++;
			while (tokens)
			{
				printf("%s\n", tokens->content);
				tokens = tokens->next;
			}
			printf("\nvishel\n\n");

//			cmd_args = parser(tokens, &fd);
//
//			builtins(&params, ch);

			free_params(&params);
			free_fd(&fd);
			ft_lstclear(&tokens, del_content);
		}
		free(line);
	}
	return (status);
	//     echo -n '<   "qwerty"   >'     4qwerty4     '<   qwerty   >''<   "qwerty"   >'    4qwerty4    '<   qwerty   >' >> file.txt | grep -lE "main"
}
