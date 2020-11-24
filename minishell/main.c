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
	if (params->args)
		ft_lstclear(&params->args, &del_content);
	if (params->command)
		free(params->command);
	if (params->flags)
		free(params->flags);
	if (params->redir)
		free(params->redir);
	if (params->name_fd)
		free(params->name_fd);
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
	char		*line;
//	char		*curr;
	int			ch;
	int			err;

	if (!(env = copy_envp_to_struct(envp)))
		return (-1);
	/* while (env) */
	/* { */
	/* 	printf("<%s=%s>\n", env->name, env->value); */
	/* 	env = env->next; */
	/* } */
	while (TRUE)
	{
		wait_line("minishell$ ");

		if ((err = get_next_line(0, &line)) < 0)
		{
			return (-1);
			printf("<%s>\n", line);
			/* curr = line; */
			/* while (*curr) */
			/* { */
			/* 	printf("%c", *curr); */
			/* 	curr++; */
			init_params(&params);
			/* ch = parser(&params, line); */
			/* builtins(&params, ch); */
			/* free_params(&params); */
			/* } */
			/* printf("\n"); */
			free(line);
		}
		if (err == 0)
			free(line);
		printf("<%s>\n", line);
		/* curr = line; */
		/* while (*curr) */
		/* { */
		/* 	printf("%c", *curr); */
		/* 	curr++; */
		init_params(&params);
		/* ch = parser(&params, line); */
		/* builtins(&params, ch); */
		/* free_params(&params); */
		/* } */
		/* printf("\n"); */
		free(line);
		if (err == -1) // free all
			return (-1);
	}
	return (0);
}
