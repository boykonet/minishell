/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:05:19 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/18 21:05:19 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_echo(char **args, char *flags, t_env *env)
{
	char	*result;
	char	*curr;
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		j = 0;
		curr = args[i];
		while (*curr)
		{
			if (*curr == '$')
			{
				while (*curr != '$' || *curr != '\0')
					j++;
				find_
			}
			j++;
		}
		
		i++;
	}
	/* t_list	*curr; */
	/* char	*result; */
	/* char	*tmp; */
	/* int		back_slash; */
	/* int		i; */

	/* i = 0; */
	/* tmp = NULL; */
	/* back_slash = 0; */
	/* curr = params->args; */
	/* if (!ft_strncmp(params->flags, "n", 1)) */
	/* 	back_slash = 1; */
	/* if (!(result = ft_strdup(""))) */
	/* 	return (NULL); */
	/* while (curr) */
	/* { */
	/* 	tmp = result; */
	/* 	if (!(result = ft_strjoin(result, curr->content))) */
	/* 	{ */
	/* 		free(tmp); */
	/* 		free_params(params); */
	/* 		return (NULL); */
	/* 	} */
	/* 	/1* if (params->args_size - i == 0) *1/ */
	/* 	/1* 	write_str(curr->content, fd, 1); *1/ */
	/* 	/1* else *1/ */
	/* 	/1* 	write_str(curr->content, fd, 0); *1/ */
	/* 	curr = curr->next; */
	/* 	i++; */
	/* } */
	/* if (back_slash == 0) */
	/* 	write(fd, "\n", 1); */
	return (result);
}
