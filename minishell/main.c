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
		free_string(params->args);
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

t_env		*copy_envp_to_struct(char **envp)
{
	t_env	*env;
	t_env	*curr;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(env = ft_lstnew_env(NULL, NULL)))
		return (NULL);
	curr = env;
	tmp = ft_strchr(envp[i], '=');
	curr->name = ft_substr(envp[i], 0, tmp - envp[i]);
	curr->value = ft_substr(tmp, 1, ft_strlen(envp[i]));
	while (envp[++i])
	{
		if (!(curr->next = ft_lstnew_env(NULL, NULL)))
			return (NULL);
		curr = curr->next;
		tmp = ft_strchr(envp[i], '=');
		curr->name = ft_substr(envp[i], 0, tmp - envp[i]);
		curr->value = ft_substr(tmp, 1, ft_strlen(envp[i]));
	}
	return (env);
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
	while (env)
	{
		printf("<%s=%s>\n", env->name, env->value);
		env = env->next;
	}
	/* while (TRUE) */
	/* { */
	/* 	wait_line("minishell$ "); */

	/* 	while ((err = get_next_line(0, &line)) > 0) */
	/* 	{ */
	/* 		printf("<%s>\n", line); */
	/* 		/1* curr = line; *1/ */
	/* 		/1* while (*curr) *1/ */
	/* 		/1* { *1/ */
	/* 		/1* 	printf("%c", *curr); *1/ */
	/* 		/1* 	curr++; *1/ */
	/* 		init_params(&params); */
	/* 		/1* ch = parser(&params, line); *1/ */
	/* 		/1* builtins(&params, ch); *1/ */
	/* 		/1* free_params(&params); *1/ */
	/* 		/1* } *1/ */
	/* 		/1* printf("\n"); *1/ */
	/* 		free(line); */
	/* 	} */
	/* 	if (err == -1) // free all */
	/* 		return (-1); */
	/* } */
	return (0);
}
